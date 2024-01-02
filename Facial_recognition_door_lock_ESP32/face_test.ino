//face_test.c
#include "Arduino.h"
#include "fd_forward.h"
#include "fr_forward.h"
#include "fr_flash.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_camera.h"
#include "camera_index.h"
#include <ArduinoWebsockets.h>

//WiFi账号密码  
const char* ssid     = "---";   //网络名称
const char* password = "---"; //网络密码
#define ENROLL_CONFIRM_TIMES 5
#define FACE_ID_SAVE_NUMBER 7

//选择摄像头种类(我们用的是AI_THINKER)
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

using namespace websockets;
WebsocketsServer socket_server;

camera_fb_t * fb = NULL;

#define relay_pin 2            //定义继电器引脚
unsigned long door_opened_millis = 0;
long interval = 5000;           // 开锁时间5000ms
bool face_recognised = false;

long last_millis = 0;  //上一次检测时间

//esp32-cam初始化一个服务器
void server_init();

typedef struct
{
  uint8_t *image;
  box_array_t *net_boxes;
  dl_matrix3d_t *face_id;
} http_img_process_result;

//提前配置好MTMN人脸检测模型的参数，参阅通用方案
static inline mtmn_config_t mtmn_config_func()
{
  mtmn_config_t mtmn_config = {0};
  mtmn_config.type = FAST;
  mtmn_config.min_face = 80;
  mtmn_config.pyramid = 0.707;
  mtmn_config.pyramid_times = 4;
  mtmn_config.p_threshold.score = 0.6;
  mtmn_config.p_threshold.nms = 0.7;
  mtmn_config.p_threshold.candidate_number = 20;
  mtmn_config.r_threshold.score = 0.7;
  mtmn_config.r_threshold.nms = 0.7;
  mtmn_config.r_threshold.candidate_number = 10;
  mtmn_config.o_threshold.score = 0.7;
  mtmn_config.o_threshold.nms = 0.7;
  mtmn_config.o_threshold.candidate_number = 1;
  return mtmn_config;
}
mtmn_config_t mtmn_config = mtmn_config_func();

face_id_name_list st_face_list;
static dl_matrix3du_t *aligned_face = NULL;
httpd_handle_t camera_httpd = NULL;

//定义摄像头所处模式的类型camera_state
typedef enum
{
  START_STREAM,
  START_DETECT,
  SHOW_FACES,
  START_RECOGNITION,
  START_ENROLL,
  ENROLL_COMPLETE,
  DELETE_ALL,
} en_fsm_state;
en_fsm_state camera_state;

typedef struct
{
  char enroll_name[ENROLL_NAME_LEN];
} httpd_resp_value;

httpd_resp_value st_name;

//人脸识别初始化
void face_init();

void setup() {
  Serial.begin(115200);         //串口通讯时的数据传输速率为115200
  Serial.setDebugOutput(true);
  Serial.println();

//定义继电器模块的引脚模式，并将继电器初始化为低电平。
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);

//摄像头初始化配置,创建camera_config_t类对象config
  camera_config_t config;
  //时钟配置
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  //Pin IO口引脚
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  //FPS帧率配置，对于ov2640，可以为20KHz或者10KHz
  config.xclk_freq_hz = 20000000;
  //数据像素格式设置为JPEG
  config.pixel_format = PIXFORMAT_JPEG;
  //
  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA; //图像帧大小
    config.jpeg_quality = 10; //JPEG压缩
    config.fb_count = 2; //缓存帧数量
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

// 用config对象初始化摄像头驱动，只调用一次
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("摄像头初始化错误，错误代码：0x%x", err);
    return;
  }

//获取摄像头传感器，对传感器做一些配置
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_QVGA);

//连接wifi路由
  WiFi.begin(ssid, password);  //连接网络
  while (WiFi.status() != WL_CONNECTED) //等待网络连接成功
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi连接成功"); //网络连接成功

//启动web服务器
  server_init();
  face_init();
  socket_server.listen(82);//监听82端口
  Serial.print("摄像头初始化完成，请使用 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' 访问网站");
}

static esp_err_t index_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");
  httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
  return httpd_resp_send(req, (const char *)index_ov2640_html_gz, index_ov2640_html_gz_len);
}

httpd_uri_t index_uri = {
  .uri       = "/",
  .method    = HTTP_GET,
  .handler   = index_handler,
  .user_ctx  = NULL
};

//创建web服务器函数server_init
void server_init ()
{
  httpd_config_t config = HTTPD_DEFAULT_CONFIG(); 
  if (httpd_start(&camera_httpd, &config) == ESP_OK) //创建 HTTP 服务器的实例camera_httpd
    Serial.println("网页开始服务");
  {
    httpd_register_uri_handler(camera_httpd, &index_uri); //注册 URI 处理程序
  }
}

//读取人脸数据函数face_init
void face_init()
{
  face_id_name_init(&st_face_list, FACE_ID_SAVE_NUMBER, ENROLL_CONFIRM_TIMES);
  aligned_face = dl_matrix3du_alloc(1, FACE_WIDTH, FACE_HEIGHT, 3);//为已登记的人脸分配内存
  read_face_id_from_flash_with_name(&st_face_list);
}

//登记人脸信息的函数do_enrollment
static inline int do_enrollment(face_id_name_list *face_list, dl_matrix3d_t *new_id)
{
  ESP_LOGD(TAG, "START ENROLLING");
  int left_sample_face = enroll_face_id_to_flash_with_name(face_list, new_id, st_name.enroll_name);
  ESP_LOGD(TAG, "面部ID：%s  样本编号：%d",
           st_name.enroll_name,
           ENROLL_CONFIRM_TIMES - left_sample_face);
  return left_sample_face;
}

void dealing_mes(WebsocketsClient &client, WebsocketsMessage msg)
{
  if (msg.data() == "stream") {
    camera_state = START_STREAM;
    client.send("开始视频检测");
  }
  if (msg.data() == "detect") {
    camera_state = START_DETECT;
    client.send("正在检测人脸");
  }
  if (msg.data().substring(0, 8) == "capture:") {
    camera_state = START_ENROLL;
    char person[FACE_ID_SAVE_NUMBER * ENROLL_NAME_LEN] = {0,};
    msg.data().substring(8).toCharArray(person, sizeof(person));
    memcpy(st_name.enroll_name, person, strlen(person) + 1);
    client.send("正在录入人脸");
  }
  if (msg.data() == "recognise") {
    camera_state = START_RECOGNITION;
    client.send("正在识别人脸");
  }
  if (msg.data().substring(0, 7) == "remove:") {
    char person[ENROLL_NAME_LEN * FACE_ID_SAVE_NUMBER];
    msg.data().substring(7).toCharArray(person, sizeof(person));
    delete_face_id_in_flash_with_name(&st_face_list, person);
    send_face_list(client); // reset faces in the browser
  }
  if (msg.data() == "delete_all") {
    delete_all_faces(client);
  }
}

//发送人脸函数
static esp_err_t send_face_list(WebsocketsClient &client)
{
  client.send("删除所有人脸");
  face_id_node *head = st_face_list.head;
  char add_face[64];
  for (int i = 0; i < st_face_list.count; i++) // loop current faces
  {
    sprintf(add_face, "人脸列表:%s", head->id_name); //字符串复制到add_face
    client.send(add_face); //发送人脸
    head = head->next;
  }
}

//删除人脸函数
static esp_err_t delete_all_faces(WebsocketsClient &client)
{
  delete_face_all_in_flash_with_name(&st_face_list);
  client.send("删除所有人脸");
}

//开锁函数
void open_door(WebsocketsClient &client) {
  if (digitalRead(relay_pin) == LOW) {
    digitalWrite(relay_pin, HIGH); //关闭（通电）继电器，使门解锁
    Serial.println("门已解锁!");
    client.send("门已解锁！");
    door_opened_millis = millis(); // 时间继电器关闭，门打开
  }
}


//开始循环工作
void loop() {
  auto client = socket_server.accept();
  client.onMessage(dealing_mes); //客户端接受数据通过调用dealing_mes()改变camera_state的值
  dl_matrix3du_t *image_matrix = dl_matrix3du_alloc(1, 320, 240, 3); //为图像矩阵分配内存
  http_img_process_result out_res = {0}; //初始化out_res
  out_res.image = image_matrix->item;

  send_face_list(client);
  client.send("开始视频检测");

  while (client.available()) {
    client.poll();

    if (millis() - interval > door_opened_millis) { //当前时间-上一次开门时间>开锁时间间隔
      digitalWrite(relay_pin, LOW); //锁门

    fb = esp_camera_fb_get();//获取视频流

    if (camera_state == START_DETECT || camera_state == START_ENROLL || camera_state == START_RECOGNITION)
    {
      out_res.net_boxes = NULL;
      out_res.face_id = NULL;

      fmt2rgb888(fb->buf, fb->len, fb->format, out_res.image);//将视频转化为RGB888

      out_res.net_boxes = face_detect(image_matrix, &mtmn_config);//进行人脸检测

      if (out_res.net_boxes)//如果检测到人脸
      {
        if (align_face(out_res.net_boxes, image_matrix, aligned_face) == ESP_OK)//如果人脸对齐正确
        {
          out_res.face_id = get_face_id(aligned_face); //提取人脸特征值
          last_millis = millis(); //将上一次检测时间改为当前时间
          
          //如果是检测模式START_DETECT
          if (camera_state == START_DETECT) {
            client.send("人脸检测中");
          }
          
          //如果是录入模式START_ENROLL
          if (camera_state == START_ENROLL)
          {
            int left_sample_face = do_enrollment(&st_face_list, out_res.face_id);
            char enrolling_message[64];
            sprintf(enrolling_message, "样本编号：%d 对应面部ID %s", ENROLL_CONFIRM_TIMES - left_sample_face, st_name.enroll_name);
            client.send("正在登记");
            
            //如果人脸已被占用
            if (left_sample_face == 0)
            {
              ESP_LOGI(TAG, "登记的人脸ID: %s", st_face_list.tail->id_name);
              camera_state = START_STREAM;
              char captured_message[64];
              sprintf(captured_message, "但该面部已被样本编号：%s占用", st_face_list.tail->id_name);
              client.send("该面部已被占用");
              send_face_list(client);
            }
          }

          //如果是识别模式START_RECOGNITION
          if (camera_state == START_RECOGNITION  && (st_face_list.count > 0))
          {
            face_id_node *f = recognize_face_with_name(&st_face_list, out_res.face_id);//人脸特征进行对比

            //如果识别成功
            if (f)
            {
              char recognised_message[64];
              sprintf(recognised_message, "门被 %s 打开了", f->id_name);
              open_door(client); //打开门
              client.send(recognised_message);
            }
            else
            {
              client.send("该脸未被认出");
            }
          }
          dl_matrix3d_free(out_res.face_id); //在检测到的人脸特征中删除掉已经识别过的人脸特征
        }

      }
      //检测人脸失败
      else
      {
        if (camera_state != START_DETECT) {
          client.send("没有检测到人脸");
        }
      }

      //正在检测但未检测到人脸
      if (camera_state == START_DETECT && millis() - last_millis > 500) //已经检测了500ms以上
      { 
        client.send("正在检测");
      }

    }

    client.sendBinary((const char *)fb->buf, fb->len); //传输视频流的buf(Pointer to the pixel data)和len(Length of the buffer in bytes)到客户端

    esp_camera_fb_return(fb); //获取摄像头帧数据，复用帧数组
    fb = NULL; //fb置空，准备下一次循环
  }
}
}
