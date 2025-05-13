#include<iostream>
#include<behaviortree_cpp/bt_factory.h>
#include<behaviortree_cpp/action_node.h>

using namespace std;

class SaySomething : public BT::SyncActionNode{
public:
  SaySomething(const string &name, const BT::NodeConfig &config) : SyncActionNode(name, config){}

  static BT::PortsList providedPorts(){
    return {BT::InputPort<string>("message")};
  }

  BT::NodeStatus tick() override{
    BT::Expected<string> msg = BT::TreeNode::getInput<string>("message");
    if (!msg){
      throw BT::RuntimeError("missing required input [message]: ", msg.error());
    }
    cout << "Robot Says: " << msg.value() << endl;
    return BT::NodeStatus::SUCCESS;
  } 
};

class ThinkWhatToSay : public BT::SyncActionNode{
public:
  ThinkWhatToSay(const string &name, const BT::NodeConfig &config) : SyncActionNode(name, config) {}

  static BT::PortsList providedPorts(){
    return {BT::OutputPort<string>("text")};
  }

  BT::NodeStatus tick() override{
    BT::TreeNode::setOutput("text", "The answer is 42");
    return BT::NodeStatus::SUCCESS;
  }
};

int main(){
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");
  auto tree = factory.createTreeFromFile("./../tree.xml");
  tree.tickWhileRunning();
  return 0;
}