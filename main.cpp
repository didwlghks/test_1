#include <ros/ros.h>
#include <motor_test/motor_node.h>
//#include <my_msgs/CameraData.h>
//#include <my_msgs/SensorData.h>
#include <my_msgs/SignalData.h>
#include <iostream>

////////////////////////////////////
#define X_BOUND_1 -100
#define X_BOUND_2 100
#define BIG_SIZE 500
#define SENSOR_LIMIT 50
///////////////////////////////////// define value, 일단 임의값으로 해놓음
/*
/////////////////////////////
bool person_detect = false;
bool sign_detect = false;

float person_x = 0;
float person_size = 0;
float sign_x = 0;
float sign_size = 0;
*/
/////////////////////////////// cam data

/*
/////////////////////////// 
float FrontSensor = 0;
float LeftSensor = 0;
float RightSensor = 0;
float BackSensor = 0;
////////////////////////// sensor data
*/

///////////////
int state = 0; // display data
///////////////


int sequence = 0; // sequence 0 to 3

/*
void CamDataCallback(const my_msgs::CameraData& msg) { // function which subscribes from camera
    person_detect = msg.p_detect;
    person_x = msg.p_x;
    person_size = msg.p_size;
    sign_detect = msg.s_detect;
    sign_x = msg.s_x; 
    sign_size = msg.s_size; //동현이형이랑 메시지명 맞춰야되는 부분 p_detect, p_x 등 
}

void SensorDataCallback(const my_msgs::SensorData& msg) {
    FrontSensor = msg.front;
    LeftSensor = msg.left;
    RightSensor = msg.right;
    BackSensor = msg.back;
}
*/
void SignalDataCallback(const my_msgs::SignalData& msg) {
    state = msg.data;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "motor_node");
  ros::NodeHandle nh;
  Initialize();
  ros::Publisher signal_pub = nh.advertise<my_msgs::SignalData>("/signal/topic", 10);
  ros::Subscriber signal_sub = nh.subscribe("/signal/topic2", 10, SignalDataCallback);
  //ros::Subscriber sensor_sub = nh.subscribe("/sensor/topic", 10, SensorDataCallback);
  //ros::Subscriber camera_sub = nh.subscribe("/camera/topic", 10, CamDataCallback); //camera topic sub
  ros::Rate loop_rate(Control_cycle);
  my_msgs::SignalData signal_msg;

  while(ros::ok())
  {
      
    switch(sequence)
    {
        case 0:

            Motor_Controller(1, true, 30);
            Motor_Controller(2, false, 30);
            signal_msg.data++;
            if(signal_msg.data > 5)
            {
              signal_pub.publish(signal_msg);
              sequence++;
              break;
            }
            

        case 1:
            
                signal_sub;

                if (state == 9999) // 9999 = display's end_signal
                {
                    sequence = 0;
                    break;
                }
    }
    
    ros::spinOnce();
    loop_rate.sleep();
  }
  Motor_Controller(1, true, 0);
  Motor_Controller(2, true, 0); //노드 종료시 무조건 모터정지
  return 0;
}






