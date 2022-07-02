#include "ros/ros.h" //ROSをc++で使えるようにする
#include "std_msgs/String.h"
#include "topic_sample_mix/message_file.h" //"パッケージ名/拡張子なしmsgファイル名.h"

class Publisher{ //パブリッシャのクラス
    public: //publicメンバとして関数を定義
        Publisher();
        void publish_msg(void);
    private: //privateメンバとして変数を定義
        ros::NodeHandle nh; //ROSと通信するためのノードハンドルの作成
        ros::Publisher publisher; //パブリッシャの定義
        topic_sample_mix::message_file msg; //msgファイルで定義したメッセージのインスタンス生成
        int count = 0; //count変数の定義と初期化
};

Publisher::Publisher(){
    publisher = nh.advertise<topic_sample_mix::message_file>("topic_name", 1000); //パブリッシャのインスタンス生成
}

void Publisher::publish_msg(void){ 
    ros::Rate loop_rate(1); //1秒間に1回（1Hz）
    while (ros::ok()){ //Ctrl+Cで強制終了やエラーが発生しない間ずっとループ
        msg.count = count; //msgファイルで定義したcountに代入
        ROS_INFO("%d", msg.count); //ログの表示
        publisher.publish(msg); //メッセージをトピックに配信（送信）
        loop_rate.sleep(); //待機
        ++count; //countを1増やす
    }
}

int main(int argc, char **argv){ //メイン関数
    ros::init(argc, argv, "publisher_node"); //ノードの初期化
    Publisher pub; //クラスのインスタンス生成
    pub.publish_msg(); //クラス内の関数にアクセス（実行）
    return 0; //終了
}