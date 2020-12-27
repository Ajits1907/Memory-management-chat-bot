#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////

    // delete _chatBot; //Task 0

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

//Task 4 exclusive ownership of child edges
// void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> &&edge)
{
    // _childEdges.push_back(edge);
    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
// void GraphNode::MoveChatbotHere(ChatBot *chatbot)
void GraphNode::MoveChatbotHere(ChatBot &&chatbot)
{
    _chatBot = ChatBot(std::move(chatbot));
    _chatBot.GetChatLogicHandle()->SetChatbotHandle(&_chatBot);

    _chatBot.SetCurrentNode(this);
    // _chatBot = chatbot;
    // _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    ChatBot tmpbot = ChatBot();
    tmpbot.SetRootNode(_chatBot.GetRootNode()); // Set the root node
    tmpbot.SetChatLogicHandle(_chatBot.GetChatLogicHandle());
    tmpbot.SetImageHandle(_chatBot.GetImageHandle());
    newNode->MoveChatbotHere(std::move(tmpbot));
    // newNode->MoveChatbotHere(_chatBot);
    // _chatBot = nullptr; // invalidate pointer at source
    _chatBot.SetImageHandle(nullptr); // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    // return _childEdges[index];
    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}