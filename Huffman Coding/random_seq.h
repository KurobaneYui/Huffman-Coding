#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<random>

using namespace std;

struct Node // 节点，每个待编码字符为一个节点
{
	string content = ""; // 待编码字符（串）
	double probility { 0 }; // 待编码字符（串）的概率,第一个为初始概率，第二个用于编码过程（使用者可忽略）
	string current_coding = ""; // 对应编码，在编码过程中不断加入新的位
	Node* next = NULL; // 指向分成一组的下一个字符（串）节点
};

class StringSeque // 随机概率序列发生器，指定序列长度，返回一个序列，各元素概率总和为1
{
public:
	StringSeque(unsigned int length); // 实例化的时候需指定序列长度
	~StringSeque();

	vector<Node>get_NewSequece(); // 获取一个新的序列
	vector<Node>get_LastSequence(); // 重新返回最近一次产生的序列
	bool change_length(unsigned int length); // 更改序列长度

private:
	bool can_create_seq = false; // 序列长度是否已经设定在合理值区间
	vector<Node>Node_seq{}; // 存储序列用的向量
	unsigned int seq_length{}; // 序列长度
	default_random_engine random_probility; // 随机数发生器
	uniform_int_distribution<unsigned int>probility_uniform_0_10000{ 0,10000 }; // 0~10000范围内的均匀分布
};

StringSeque::StringSeque(unsigned int length)
{
	if (length > 0 and length < 6553) { // 长度在1~6552内，也可以再扩大，但是没必要
		seq_length = length;
		cout << "设定序列长度为：" << length << endl;
		can_create_seq = true;
	}
	else {
		cout << endl << "错误！！超出范围（1~6552）的序列长度：" << length << endl;
		can_create_seq = false;
	}
}

StringSeque::~StringSeque()
{
}

inline vector<Node> StringSeque::get_NewSequece()
{
	if (!can_create_seq) {
		cout << endl << "序列长度不符合要求，请重新设定" << endl;
		return;
	}
	unsigned long long int totle{ 0 }; // 随机值总和
	Node_seq.clear(); // 清除已有的元素
	random_probility.seed(chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count()); // 用一个新的随机数种子设定发生器
	for (unsigned int i = seq_length; i > 0; i--) {
		Node node;
		node.probility = probility_uniform_0_10000(random_probility); // 产生一个概率在0~10000内均匀分布的随机整数
		node.content = to_string(i); // 设定新元素
		Node_seq.push_back(node); // 压入向量
		totle += node.probility;
	}
	for (unsigned int i = 0; i < seq_length; i++) {
		Node_seq[i].probility /= totle; // 利用随机值总和对概率归一化，得到各元素的概率，这样概率总和为1
	}
	return Node_seq;
}

inline vector<Node> StringSeque::get_LastSequence()
{
	if (Node_seq.size() == 0) {
		cout << endl << "警告！！还未生成序列。程序将生成新序列，序列长度为：" << seq_length << endl;
		return get_NewSequece();
	}
	else {
		return Node_seq;
	}
}

inline bool StringSeque::change_length(unsigned int length)
{
	if (length > 0 and length < 6553) {
		seq_length = length;
		cout << "序列长度变更为：" << length << endl;
		return can_create_seq = true;
	}
	else {
		cout << endl << "错误！！超出范围（1~6552）的序列长度：" << length << endl;
		return can_create_seq = false;
	}
}
