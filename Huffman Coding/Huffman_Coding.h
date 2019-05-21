#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<chrono>

using namespace std;

struct CodingNode // 节点，每个待编码字符为一个节点
{
	string content = ""; // 待编码字符（串）
	double probility[2] = { 0,0 }; // 待编码字符（串）的概率,第一个为初始概率，第二个用于编码过程（使用者可忽略）
	string current_coding = ""; // 对应编码，在编码过程中不断加入新的位
	CodingNode* next = NULL; // 指向分成一组的下一个字符（串）节点
};

struct CodingNode_cmp // 用来比较指针形式的字符（串）节点的大小。提供给优先队列使用
{
	bool operator()(CodingNode*& a, CodingNode*& b) const
	{
		return a->probility[1] > b->probility[1]; // 比较节点的概率，大于号表示优先队列概率小的优先
	}
};

class Huffman_CodingTree // Huffman编码树，提供字符（串）和对应的概率，返回指定进制下的编码
{
public:
	Huffman_CodingTree(unsigned int r = 2); // 构造函数，默认为2进制霍夫曼，也可更改为其他
	~Huffman_CodingTree(); // 析构函数

	bool change_codingSystem(unsigned int r = 2); // 改变编码进制
	bool add_Node(CodingNode* node); // 添加待编码节点，参数为节点的指针
	bool add_Node(string content, double probility); // 添加待编码节点，参数为节点的字符（串）和概率。将自动转换为节点并存入
	bool remove_Node(CodingNode* node); // 移除某个节点
	bool remove_Node(string content); // 根据待编码字符（串）移除某个节点
	bool clear_all_Node(); // 清空节点
	CodingNode* Node_exist(CodingNode* node); // 检查某节点是否存在
	bool start_coding(); // 开始编码
	vector<CodingNode*> get_coding(); // 返回字符（串）以及对应的概率和编码
	bool output_coding(); // 输出字符（串）以及对应的概率和编码
	vector<double> get_para(); // 返回参数：熵、平均码长、编码效率
	bool output_para(); // 输出参数：熵、平均码长、编码效率

private:
	unsigned int R; // 存储进制信息
	bool finished = false; // 是否已完成编码
	double totle_probility = 0; // 存储概率总和
	priority_queue<CodingNode*, vector<CodingNode*>, CodingNode_cmp>Node_ptr{}; // 存储待编码节点的优先队列，用于编码
	vector<CodingNode*>Node_vec; // 存储待编码节点原始信息的向量，用于初始化优先队列，以及最终返回信息

	bool vec2que(); // 节点从vector容器压入priority_queue队列
	bool clear_priority_queue(); // 清空优先队列
	bool addCode(string code,CodingNode* node); // 给节点添加编码新一位
	CodingNode* merge_Node(CodingNode* node_pre, CodingNode* node_sub); // 将两个节点整合为一个，实际是将一个节点变为另一个节点的子节点
};

Huffman_CodingTree::Huffman_CodingTree(unsigned int r)
{
	cout << endl << "***已创建编码树，编码为“ " << r << " ”进制Huffman编码" << endl;
	if (r < 2) { // 如果进制数小于2，报错
		cout << endl << "严重错误！！错误的霍夫曼编码进制：" << r << "\n\tHuffman编码的进制数应该大于等于2" << endl;
	}
	R = r;
	finished = false;
}

Huffman_CodingTree::~Huffman_CodingTree()
{
	cout << endl << "***已销毁编码树" << endl;
}

inline bool Huffman_CodingTree::change_codingSystem(unsigned int r)
{
	if (r < 2) { // 如果进制数小于2，报错
		cout << endl << "严重错误！！错误的霍夫曼编码进制：" << r << "\n\tHuffman编码的进制数应该大于等于2" << endl<<"没有改变编码进制！！仍为： " << R << " 进制进制" << endl;
		return false;
	}
	cout << endl << "***已更改编码树，编码为 " << r << " 进制Huffman编码" << endl;
	R = r;
	return true;
}

inline bool Huffman_CodingTree::add_Node(CodingNode* node)
{
	if (node->probility[0] > 1 or node->probility[0] < 0) { // 判断概率在合理范围内
		cout << endl << "概率不符合要求：0 ≦ P ≦ 1" << endl;
		return false;
	}
	if (Node_exist(node)==NULL) { // 如果节点不存在，则允许添加
		node->probility[1] = node->probility[0]; // 初始化用于编码的概率
		Node_vec.push_back(node);
		totle_probility += node->probility[0];
		cout << "已添加字符串\n\t" << node->content << "概率为" << node->probility[0] << endl;
		return true;
	}
	else if (node->probility[0] == 0) { // 如果添加的节点概率为0，允许添加
		node->probility[1] = node->probility[0]; // 初始化用于编码的概率
		Node_vec.push_back(node);
		cout << "已添加概率为0的节点，节点对应的字符（串）不会在最后输出" << endl;
		return true;
	}
	else { // 如果节点存在，且待添加的节点概率不为0，不予添加
		cout << endl << "不能添加该字符（串）\n\t" << node->content << "\n\t字符（串）对应的节点已存在，概率为" << Node_exist(node)->probility[0] << endl;
		return false;
	}
}

inline bool Huffman_CodingTree::add_Node(string content, double probility)
{
	CodingNode* node = new CodingNode; // 自动完成节点信息的补全
	node->content = content;
	node->probility[0] = probility;
	node->current_coding = "";
	node->next = NULL;
	return add_Node(node); // 尝试添加节点
}

inline bool Huffman_CodingTree::remove_Node(CodingNode* node)
{
	vector<CodingNode*>::iterator current_node;
	for (current_node = Node_vec.begin(); current_node != Node_vec.end(); current_node++) { // 搜索节点，存在则删除，不存在则返回false
		if ((*current_node)->content == node->content and (*current_node)->probility[0] == node->probility[0]) {
			Node_vec.erase(current_node);
			totle_probility -= (*current_node)->probility[0];
			return true;
		}
	}
	return false;
}

inline bool Huffman_CodingTree::remove_Node(string content)
{
	bool re = false;
	vector<CodingNode*>::iterator current_node;
	for (current_node = Node_vec.begin(); current_node != Node_vec.end(); current_node++) { // 搜索字符（串）对应的节点，存在则删除，不存在则返回
		if ((*current_node)->content == content) {
			Node_vec.erase(current_node);
			re = true;
		}
	}
	return re;
}

inline bool Huffman_CodingTree::clear_all_Node()
{
	Node_vec.clear(); // 清空节点vector
	return true;
}

inline CodingNode* Huffman_CodingTree::Node_exist(CodingNode* node)
{
	vector<CodingNode*>::iterator current_node;
	for (current_node = Node_vec.begin(); current_node != Node_vec.end(); current_node++) { // 检索节点
		if ((*current_node)->content == node->content)return *current_node; // 搜索到则返回节点指针
	}
	return NULL; // 没有搜索到则返回NULL
}

inline bool Huffman_CodingTree::start_coding()
{
	finished = false;
	if (R < 2) { // 判断进制是否非法
		cout << endl << "错误！！Huffman编码的进制应大于2，而设定的编码为：" << R << endl;
		return false;
	}

	if (float(totle_probility) != 1) { // 如果概率之和不为1，提示警告信息
		cout << endl << "警告！！概率之和不为1，编码仍将继续，但相关参数（熵、平均码长、编码效率）将出现较大偏差" << endl << "如果这不符合预期，请检查各节点，现有节点概率之和为：" << totle_probility << endl;
	}

	cout << endl << "***开始编码" << endl;
	auto start_time = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch());

	if (Node_vec.size() == 0) { // 如果没有需要编码的节点，提示后返回
		cout << "没有等待编码的字符（串）" << endl;
		return false;
	}
	else if (Node_vec.size() == 1) { // 直接编码为0
		Node_vec.front()->current_coding = "0";
	}
	else { // 添加概率为0的节点，辅助编码
		for (int i = (Node_vec.size() - 1) % (R - 1); i < R - 1 and i != 0; i++) {
			add_Node("",0);
		}
	}

	clear_priority_queue(); // 清空优先队列，为编码做准备
	vec2que(); // 将vector中的节点压入优先队列

	vector<CodingNode*>Node_t; // 预定义临时vector
	while (Node_ptr.size() > 1) { // 执行代码直到优先队列中只有一个节点
		for (unsigned int count = 0; count < R; count++) { // 选择概率最小的R个节点
			Node_t.push_back(Node_ptr.top()); // 弹出的节点暂存于Node_t容器中
			Node_ptr.pop();
			addCode(to_string(count), Node_t.back()); // 向这些节点添加编码位
		}

		while (Node_t.size() > 1) // 直到临时vector中只有一个节点
		{
			Node_t[0] = merge_Node(Node_t.front(), Node_t.back());
			Node_t.pop_back();
		}
		Node_ptr.push(Node_t.front()); // 将临时vector中的一个节点压入优先队列
		Node_t.clear(); // 清空临时vector
	}
	auto end_time = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch());
	cout << endl << "***编码结束，耗时" << (end_time - start_time).count()/1000.0 << " 毫秒" << endl;

	finished = true;
	return true;
}

inline vector<CodingNode*> Huffman_CodingTree::get_coding()
{
	vector<CodingNode*> Nodes;
	if (finished == false) {
		cout << endl << "没有编码，请检查是否调用start_coding()方法，或检查该方法是否返回错误信息" << endl;
		return Nodes;
	}
	CodingNode* Node_t = Node_ptr.top();
	while (Node_t != NULL)
	{
		if (Node_t->probility[0] != 0) {
			Nodes.push_back(Node_t);
		}
		Node_t = Node_t->next;
	}
	return Nodes;
}

inline bool Huffman_CodingTree::output_coding()
{
	if (finished == false) {
		cout << endl << "没有编码，请检查是否调用start_coding()方法，或检查该方法是否返回错误信息" << endl;
		return false;
	}
	for (auto i : get_coding()) {
		cout << "字符（串）：" << i->content << "  概率：" << i->probility[0] << "  编码：" << i->current_coding << endl;
	}
	return true;
}

inline vector<double> Huffman_CodingTree::get_para()
{
	vector<double> para;
	if (finished == false) {
		cout << endl << "没有编码信息，请检查是否调用start_coding()方法，或检查该方法是否返回错误信息" << endl;
		return para;
	}
	long double H{ 0 }, ita{ 0 }, l{ 0 };
	for (auto i : get_coding()) {
		H -= i->probility[0] * log2(i->probility[0]);
		l += i->probility[0] * i->current_coding.size();
	}
	ita = H / l / log2(R);
	para.push_back(H);
	para.push_back(l);
	para.push_back(ita);
	return para;
}

inline bool Huffman_CodingTree::output_para()
{
	if (finished == false) {
		cout << endl << "没有编码参数，请检查是否调用start_coding()方法，或检查该方法是否返回错误信息" << endl;
		return false;
	}
	vector<double> pr;
	pr = get_para();
	cout << "熵：" << pr[0] << "  平均码长：" << pr[1] << "  编码效率：" << pr[2] * 100 << " %" << endl;
	return true;
}

inline bool Huffman_CodingTree::vec2que()
{
	vector<CodingNode*>::iterator current_node;
	for (current_node = Node_vec.begin(); current_node != Node_vec.end(); current_node++) {
		Node_ptr.push(*current_node); // 将每一个vector元素压入优先队列priority_queue
	}
	return true;
}

inline bool Huffman_CodingTree::clear_priority_queue()
{
	priority_queue<CodingNode*, vector<CodingNode*>, CodingNode_cmp>empty{};
	Node_ptr.swap(empty); // 将已有队列和空队列交换
	return true;
}

inline bool Huffman_CodingTree::addCode(string code, CodingNode* node)
{
	while (node != NULL) // 当前指针不为空时则给指向的节点添加编码位
	{
		node->current_coding = code + node->current_coding; // 添加编码位
		node = node->next; // 指向下一个节点
	}
	return true;
}

inline CodingNode* Huffman_CodingTree::merge_Node(CodingNode* node_pre, CodingNode* node_sub)
{
	node_pre->probility[1] += node_sub->probility[1]; // 将第二个节点组的整体概率并入第一个节点组
	cout << "合并两组节点: " << node_pre->content << "节点组，和" << node_sub->content << "节点组  合并后概率为：" << node_pre->probility[1] << endl;
	CodingNode* node_f = node_pre; // 记录作为第一个元素的节点信息
	while (true)
	{
		if (node_pre->next == NULL)break; // 遍历至最后一个元素则退出
		node_pre = node_pre->next; // 否则继续遍历
	}
	node_pre->next = node_sub; // 将最后一个节点的指针，指向另一个节点链的第一个节点
	return node_f; // 返回整合后的节点链的第一个节点
}
