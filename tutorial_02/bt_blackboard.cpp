#include<iostream>
#include<behaviortree_cpp/action_node.h>
#include<behaviortree_cpp/bt_factory.h>

using namespace BT;

class SaySomething : public SyncActionNode
{
public: 
  SaySomething(const std::string &name,const NodeConfig &config) : SyncActionNode(name, config)
  {

  }

  static PortsList providedPorts()
  {
    return {InputPort<std::string>("message")};
  }

  NodeStatus tick() override
  {
    Expected<std::string> msg = getInput<std::string>("message");
    if (!msg){
      throw RuntimeError("missing required input [message]: ", 
                              msg.error());
    }
    std::cout << "Robot Says: " << msg.value() << std::endl;
    return NodeStatus::SUCCESS;
  }

};

class ThinkWhatToSay : public SyncActionNode
{
public: 
  ThinkWhatToSay(const std::string &name, const NodeConfig &config) : SyncActionNode(name, config) {}

  static PortsList providedPorts()
  {
    return {OutputPort<std::string>("text")};
  }

  NodeStatus tick() override
  {
    setOutput("text", "The Answer is 42");
    return NodeStatus::SUCCESS;
  }
};

int main(){ 
  BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

  auto tree = factory.createTreeFromFile("./../tree.xml");
  tree.tickWhileRunning();
  return 0;
}