#include<iostream>
#include<behaviortree_cpp/bt_factory.h>
#include<behaviortree_cpp/action_node.h>

using namespace std;

struct Position2D 
{ 
  double x;
  double y; 
};

namespace BT
{
  template <> inline Position2D convertFromString(StringView str)
  {
    // We expect real numbers separated by semicolons
    auto parts = splitString(str, ';');
    if (parts.size() != 2)
    {
      throw RuntimeError("invalid input)");
    }
    else
    {
      Position2D output;
      output.x     = convertFromString<double>(parts[0]);
      output.y     = convertFromString<double>(parts[1]);
      return output;
    }
  }
} // end namespace BT

class CalculateGoal : public BT::SyncActionNode{
public:
  CalculateGoal(const string &name, const BT::NodeConfig &config) : SyncActionNode(name, config) {}
  
  static BT::PortsList providedPorts(){
    return {BT::OutputPort<Position2D>("goal")};
  }
  
}

int main(){
  return 0;
}