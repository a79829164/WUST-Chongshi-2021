  #include <ros/ros.h>
#include <time.h>
#include "executor/chassis_executor.h"

#include "example_behavior/back_boot_area_behavior.h"
#include "example_behavior/chase_behavior.h"
#include "example_behavior/search_behavior.h"
#include "example_behavior/escape_behavior.h"
#include "example_behavior/patrol_behavior.h"
#include "example_behavior/shoot_behavior.h"
#include "example_behavior/wait_behavior.h"
#include "example_behavior/ready_behavior.h"
#include "example_behavior/observe_behavior.h"
#include "example_behavior/F1_behavior.h"
#include "example_behavior/F2_behavior.h"
#include "example_behavior/F3_behavior.h"
#include "example_behavior/F4_behavior.h"
#include "example_behavior/F5_behavior.h"
#include "example_behavior/F6_behavior.h"
#include "example_behavior/swing_behavior.h"


#include "std_msgs/Bool.h"

int shoot_flag = 0, count = 0, which_buff = 0, getbuff_act = 0, which_buff_flag = 0;
bool Detection_flag = false;

enum BehaviorStateEnum {
    INIT = -1,
    BACKBOOT = 0,
    CHASE = 1,
    SEARCH = 2,
    ESCAPE = 3,
    PATROL = 4,
    GO_F1 = 5,
    GO_F2 = 6,
    GO_F3 = 7,
    GO_F4 = 8,
    GO_F5 = 9,
    GO_F6 = 10,
    SHOOT = 11,
    WAIT = 12,
    READY = 13,
    OBSERVE = 14,
    SWING = 15,
    STOP = 100,   
};

int main(int argc, char** argv) {

    ros::init(argc, argv, "red_wing");

    std::string full_path = ros::package::getPath("roborts_decision") + "/config/red_wing.prototxt";

    int test[6] = { 4,6,2,5,1,3 };

    auto chassis_executor = new roborts_decision::ChassisExecutor;
    auto blackboard = new roborts_decision::Blackboard(full_path);

    // Behavior State Enum
    BehaviorStateEnum last_state, cur_state;
    last_state = BehaviorStateEnum::INIT;
    cur_state = BehaviorStateEnum::INIT;

    roborts_decision::BackBootAreaBehavior  back_boot_area_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::ChaseBehavior        chase_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::SearchBehavior       search_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::EscapeBehavior       escape_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::PatrolBehavior       patrol_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::ShootBehavior       shoot_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::WaitBehavior       wait_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::F1Behavior       f1_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::F2Behavior       f2_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::F3Behavior       f3_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::F4Behavior       f4_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::F5Behavior       f5_behavior(chassis_executor, blackboard, full_path);
    roborts_decision::F6Behavior       f6_behavior(chassis_executor, blackboard, full_path);
      roborts_decision::ReadyBehavior       ready_behavior(chassis_executor, blackboard, full_path);
  roborts_decision::ObserveBehavior       observe_behavior(chassis_executor, blackboard, full_path);
  roborts_decision::SwingBehavior      swing_behavior(chassis_executor, blackboard, full_path);



    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();

        if (blackboard->info.is_begin)
        {
            for (int i = 0; i < 7; i++)
            {
                if (blackboard->info.zone_array[i - 1] == 1) blackboard->info.red_hp_recovery = i;//0+1 = 1 ??????????????????F1???
                else if (blackboard->info.zone_array[i - 1] == 2) blackboard->info.red_bullet_supply = i;
                else if (blackboard->info.zone_array[i - 1] == 3) blackboard->info.blue_hp_recovery = i;
                else if (blackboard->info.zone_array[i - 1] == 4) blackboard->info.blue_bullet_supply = i;
                // std::cout << blackboard->info.red_hp_recovery << "\n" << blackboard->info.red_bullet_supply << "\n" << blackboard->info.blue_hp_recovery
                //     << "\n" << blackboard->info.blue_bullet_supply << "\n" << std::endl;
            }

            // for (int i = 0; i < 7; i++)
            // {
            //         if (test[i-1] == 1) blackboard->info.red_hp_recovery = i;//0+1 = 1 ??????????????????F1???
            //         else if (test[i-1] == 2) blackboard->info.red_bullet_supply = i;
            //         else if (test[i-1] == 3) blackboard->info.blue_hp_recovery = i;
            //         else if (test[i-1] == 4) blackboard->info.blue_bullet_supply = i;
            //     std::cout<<blackboard->info.red_hp_recovery<<"\n"<<blackboard->info.red_bullet_supply<<"\n"<<blackboard->info.blue_hp_recovery
            //     <<"\n"<<blackboard->info.blue_bullet_supply<<"\n"<<std::endl;
            // }

            if (getbuff_act != 0)//??????buff
            {
                             std::cout<<"getbuff_act" << std::endl;
            switch(which_buff)//??????buff???????????????????????????which_buff??????,?????????????????????????????????
            {
                case 1:
                        if(blackboard->info.red_hp_recovery == 1)  
                            {
                                cur_state = BehaviorStateEnum::GO_F1;
                                if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                         
                                }
                            }
                        else if(blackboard->info.red_hp_recovery ==2 ) 
                        {
                            cur_state = BehaviorStateEnum::GO_F2;
                            if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }
                        }
                        else if(blackboard->info.red_hp_recovery ==3 )                        
                        {    
                                cur_state = BehaviorStateEnum::GO_F3;
                            if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }
                        }
                        else if(blackboard->info.red_hp_recovery ==4 )
                        {
                            cur_state = BehaviorStateEnum::GO_F4;
                            if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }
                        }
                        else if(blackboard->info.red_hp_recovery ==5 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F5;
                            if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.red_hp_recovery ==6 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F6;
                            if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                    std::cout<<"red_hp_recovery" <<blackboard->info.red_hp_recovery << std::endl;
                    break;   
                case 2:
                        if(blackboard->info.red_bullet_supply == 1) 
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F1;
                            if(blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.red_bullet_supply ==2 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F2;
                            if(blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.red_bullet_supply ==3 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F3;
                            if(blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.red_bullet_supply ==4 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F4;
                            if(blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.red_bullet_supply ==5 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F5;
                            if(blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.red_bullet_supply ==6 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F6;
                            if(blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                    std::cout<<"red_bullet_supply" <<blackboard->info.red_bullet_supply << std::endl;
                    break;   
                case 3:
                        if(blackboard->info.blue_hp_recovery == 1)
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F1;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_hp_recovery ==2 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F2;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_hp_recovery ==3 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F3;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_hp_recovery ==4 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F4;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_hp_recovery ==5 ) 
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F5;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_hp_recovery ==6 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F6;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_hp_recovery] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        std::cout<<"blue_hp_recovery" <<blackboard->info.blue_hp_recovery << std::endl;
                    break;                   
                case 4:
                        if(blackboard->info.blue_bullet_supply == 1) 
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F1;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_bullet_supply ==2 ) 
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F2;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_bullet_supply ==3 ) 
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F3;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_bullet_supply ==4 )
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F4;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_bullet_supply ==5 ) 
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F5;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        else if(blackboard->info.blue_bullet_supply ==6 ) 
                        {                                 
                            cur_state = BehaviorStateEnum::GO_F6;
                            if(blackboard->info.zone_array_active[blackboard->info.blue_bullet_supply] == 0)  
                                {
                                        getbuff_act = 0;  //??????buff???????????????
                                        which_buff = 0;
                                }  
                        }
                        std::cout<<"blue_bullet_supply" <<blackboard->info.blue_bullet_supply << std::endl;
                    break;                    
            } 
            }


            /***********************************************************************************************************************/
            /***********************************************************************************************************************/
            /***********************************************************************************************************************/
            /***********************************************************************************************************************/


            if (getbuff_act == 0)        //???????????????
            {
                if (blackboard->info.remaining_time <= 180 && blackboard->info.remaining_time >= 165)
                {
                    //?????????buff???12???2?????????????????????????????????    
                    if (blackboard->info.red_bullet_supply == 1 || blackboard->info.red_bullet_supply == 2)
                    {
                        getbuff_act = 1;
                        which_buff = 2;
                        if (blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)  
                            cur_state = BehaviorStateEnum::WAIT;//????????????READY->SHOOT
                    }
                    else if ((blackboard->info.red_bullet_supply != 1 && blackboard->info.red_bullet_supply != 2)
                        && blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0)
                            cur_state = BehaviorStateEnum::READY;//???1???SHOOT?????????
                    else  cur_state = BehaviorStateEnum::BACKBOOT;//1??????buff????????????????????????
                }

    //    else  if(blackboard->info.remaining_time <=165 && blackboard->info.remaining_time > 150  
    //                     && blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 0        
    //                  &&???????????????1???4????????????){
    //                     cur_state = BehaviorStateEnum::BACKBOOT;
    //                  }
                /***********************************************************************************************************************/
                else if (blackboard->info.remaining_time < 150 && blackboard->info.remaining_time >= 120)
                {
                      //???????????????????????????????????????????????????1??????????????????????????????????????????buff
                    if(((blackboard->info.remain_hp_r1 <= 1500 && blackboard->info.remain_hp_r2 <= 1500) 
                        || (blackboard->info.remain_hp_r1 < 1200 || blackboard->info.remain_hp_r2 < 1200))
                        && (blackboard->info.remain_hp_r1 < blackboard->info.remain_hp_r2 && blackboard->info.remain_hp_r1 != 0))
                    {
                        getbuff_act = 1;
                        which_buff = 1;
                        if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0 )  
                            cur_state = BehaviorStateEnum::BACKBOOT;//????????????buff??????????????????????????????
                    }
            //??????????????????(????????????buff?????????????????????1)????????????????????????????????????????????????????????????????????????
                else if(blackboard->info.remain_hp_r1>1500 && blackboard->info.remain_hp_r2>1500
                            && blackboard->info.remain_bullet_r2 > 30)    
                {
                    cur_state = BehaviorStateEnum::PATROL;
                    //R1?????????????????????R1 SHOOT????????????
                if(blackboard->info.remain_hp_r1 >= 1900 && blackboard->info.remain_hp_r2 >= 1900 
                    && blackboard->info.remain_bullet_r1> 50)
                    cur_state = BehaviorStateEnum::OBSERVE; //R1 SHOOT?????????
                }
                else if(blackboard->info.remain_bullet_r2 == 0)
                    cur_state = BehaviorStateEnum::BACKBOOT;//?????????????????????????????????buff????????????????????????
                else   cur_state = BehaviorStateEnum::PATROL;//?????????????????????

                }


                /***********************************************************************************************************************/
                else if (blackboard->info.remaining_time < 120 && blackboard->info.remaining_time >= 60)
                {
                            //?????????????????????2????????????buff?????????buff????????????????????????
                            if(((blackboard->info.remain_hp_r1<1800 && blackboard->info.remain_hp_r2<1800)
                                  || (blackboard->info.remain_hp_r1<800 || blackboard->info.remain_hp_r2<800))
                                  && blackboard->info.remain_hp_r1 <= blackboard->info.remain_hp_r2)
                            {
                                if(blackboard->info.remain_hp_r2 < 800 
                                    || (blackboard->info.remain_hp_r2 > 800 && blackboard->info.remain_hp_r2 <1800
                                    && blackboard->info.remain_hp_r1 != 0))
                                    {
                                        getbuff_act = 1;
                                        which_buff = 1;
                                    }//??????1???????????????????????????
                                if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0 )
                                    cur_state = BehaviorStateEnum::READY;//??????????????????
                            }
                            else    cur_state = BehaviorStateEnum::PATROL;//??????????????????????????????
                }

     /***********************************************************************************************************************/
        else if(blackboard->info.remaining_time <60 && blackboard->info.remaining_time > 0)
        {
            if(blackboard->info.remain_hp_r1 < 300)
            {
                getbuff_act = 1;
                which_buff = 1;//???????????????
            }
            else cur_state = BehaviorStateEnum::WAIT;
            if(blackboard->info.zone_array_active[blackboard->info.red_hp_recovery] == 0 )  
            {
                if((blackboard->info.remain_hp_r1 + blackboard->info.remain_hp_r2) 
                     -(blackboard->info.remain_hp_b1 + blackboard->info.remain_hp_b2) > 500)
                     {
                        cur_state = BehaviorStateEnum::BACKBOOT;//????????????????????????????????????????????????
                     }
                     else cur_state = BehaviorStateEnum::PATROL;//????????????????????????
            }
        }

        else   cur_state = BehaviorStateEnum::PATROL;//????????????????????????????????????????????????
       
        if (blackboard->info.deep_camera_is_detected && getbuff_act == 0) cur_state = BehaviorStateEnum::SWING;
        
        if(blackboard->info.remain_hp_r2 < 300) cur_state = BehaviorStateEnum::BACKBOOT;

        if(blackboard->info.zone_array_active[blackboard->info.red_bullet_supply] == 1 
           && (blackboard->info.remain_bullet_r1<30 || blackboard->info.remain_bullet_r2<30)
           && blackboard->info.remaining_time<165
           && blackboard->info.remain_hp_r1 > blackboard->info.remain_hp_r2)
           {
                getbuff_act = 1;
                which_buff = 2;
           }
           else if(blackboard->info.zone_array_active[blackboard->info.blue_bullet_supply] == 0
            && blackboard->info.remain_bullet_r2<30 && blackboard->info.remaining_time<165)
            {
                cur_state = BehaviorStateEnum::BACKBOOT;   
            }
    }//getbuff_act == 0
}//is_begin

        if (last_state != BehaviorStateEnum::INIT && last_state != cur_state) {
            switch (last_state) {
            case BehaviorStateEnum::BACKBOOT:
                back_boot_area_behavior.Cancel();
                break;
            case BehaviorStateEnum::CHASE:
                chase_behavior.Cancel();
                break;
            case BehaviorStateEnum::SEARCH:
                search_behavior.Cancel();
                break;
            case BehaviorStateEnum::ESCAPE:
                escape_behavior.Cancel();
                break;
            case BehaviorStateEnum::PATROL:
                patrol_behavior.Cancel();
                break;
            case BehaviorStateEnum::SHOOT:
                shoot_behavior.Cancel();
                break;
            case BehaviorStateEnum::GO_F1:
                f1_behavior.Cancel();
                break;
            case BehaviorStateEnum::GO_F2:
                f2_behavior.Cancel();
                break;
            case BehaviorStateEnum::GO_F3:
                f3_behavior.Cancel();
                break;
            case BehaviorStateEnum::GO_F4:
                f4_behavior.Cancel();
                break;
            case BehaviorStateEnum::GO_F5:
                f5_behavior.Cancel();
                break;
            case BehaviorStateEnum::GO_F6:
                f6_behavior.Cancel();
                break;
      case BehaviorStateEnum::READY:
          ready_behavior.Cancel();
          break;
      case BehaviorStateEnum::OBSERVE:
          observe_behavior.Cancel();
          break;     
      case BehaviorStateEnum::SWING:
          swing_behavior.Cancel();
          break;
      case BehaviorStateEnum::STOP:
          f1_behavior.Cancel();
          f2_behavior.Cancel();
          f3_behavior.Cancel();
          f4_behavior.Cancel();
          f5_behavior.Cancel();
          f6_behavior.Cancel();
          shoot_behavior.Cancel();
          wait_behavior.Cancel();
          break;
         }
            }
        



        switch (cur_state) {
        case BehaviorStateEnum::BACKBOOT:
            back_boot_area_behavior.Run();
            std::cout << "BACKBOOT" << std::endl;
            break;
        case BehaviorStateEnum::CHASE:
            chase_behavior.Run();
            std::cout << "CHASE" << std::endl;
            break;
        case BehaviorStateEnum::SEARCH:
            search_behavior.Run();
            std::cout << "SEARCH" << std::endl;
            break;
        case BehaviorStateEnum::ESCAPE:
            escape_behavior.Run();
            std::cout << "ESCAPE" << std::endl;
            break;
        case BehaviorStateEnum::PATROL:
            patrol_behavior.Run();
            std::cout << "PATROL" << std::endl;
            break;
        case BehaviorStateEnum::SHOOT:
            shoot_behavior.Run();
            std::cout << "SHOOT" << std::endl;
            break;
        case BehaviorStateEnum::GO_F1:
            f1_behavior.Run();
            std::cout << "f2_behavior" << std::endl;
            break;
        case BehaviorStateEnum::GO_F2:
            f2_behavior.Run();
            std::cout << "f1_behavior" << std::endl;
            break;
        case BehaviorStateEnum::GO_F3:
            f3_behavior.Run();
            std::cout << "f3_behavior" << std::endl;
            break;
        case BehaviorStateEnum::GO_F4:
            f4_behavior.Run();
            std::cout << "f4_behavior" << std::endl;
            break;
        case BehaviorStateEnum::GO_F5:
            f5_behavior.Run();
            std::cout << "f5_behavior" << std::endl;
            break;
        case BehaviorStateEnum::GO_F6:
            f6_behavior.Run();
            std::cout << "f6_behavior" << std::endl;
            break;
      case BehaviorStateEnum::READY:
          ready_behavior.Run();
          std::cout<<"ready_behavior" << std::endl;
          break;
      case BehaviorStateEnum::OBSERVE:
          observe_behavior.Run();
          std::cout<<"observe_behavior" << std::endl;
          break;
      case BehaviorStateEnum::SWING:
          swing_behavior.Run();
          std::cout<<"swing_behavior" << std::endl;
          break;

        }

        last_state = cur_state;
        rate.sleep();

    }
}
