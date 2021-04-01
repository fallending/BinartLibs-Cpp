<!--
 * @Author: your name
 * @Date: 2021-03-05 11:54:06
 * @LastEditTime: 2021-03-05 16:12:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /slothjson/mtjsonv2/README.md
-->


1. https://github.com/avplayer/static_json
2. https://github.com/fallending/json
3. https://juejin.cn/post/6857044913935745031



# 

对c++来说，pb消息像这样

class PBIMChatMessage : public ::google::protobuf::MessageLite {

::google::protobuf::uint32 _has_bits_[1];
mutable int _cached_size_;
::PBIMClientInfo* client_info_;
::google::protobuf::int32 msg_type_;
::google::protobuf::int32 sender_type_;
::google::protobuf::int64 sender_id_;
::google::protobuf::int64 target_id_;
::google::protobuf::int32 target_type_;
::google::protobuf::int32 content_type_;
::std::string* content_;
::std::string* ext_content_;
::google::protobuf::int64 timestamp_;
::google::protobuf::int32 from_;

理论上可以让他支持，简单json的。。。。