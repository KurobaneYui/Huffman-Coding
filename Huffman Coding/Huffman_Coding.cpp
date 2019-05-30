#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include"Huffman_Coding.h"
#include"random_seq.h"

using namespace std;

int main(void) {

	//演示固定序列，在不同进制编码下的结果
	cout << endl << "**********以下演示指定序列在不同进制的霍夫曼编码下的结果***********" << endl;
	{
		// 建立2进制编码树，代编码符号数量5
		cout << endl << "**********5个待编码符号，2进制霍夫曼编码***********" << endl;
		Huffman_CodingTree Huf(2); // 建立编码树
		StringSeque a(5); // 定长概率序列发生器

		auto x = a.get_NewSequece(); // 生成序列
		for (unsigned int i = 0; i < x.size(); i++)
		{
			Huf.add_Node(x[i].content, x[i].probility); // 向编码树压入待编码序列
		}
		
		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率

		cout << endl << "**********转换为3进制霍夫曼编码***********" << endl;
		Huf.change_codingSystem(3);
		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率

		cout << endl << "**********转换为5进制霍夫曼编码***********" << endl;
		Huf.change_codingSystem(5);
		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率

		cout << endl << "**********转换为6进制霍夫曼编码***********" << endl;
		Huf.change_codingSystem(6);
		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率
	}

	//演示2进制下，不同待编码元素个数的编码效果
	cout << endl << "**********以下演示2进制霍夫曼编码下，不同个数待编码符号的编码结果***********" << endl;
	{
		// 建立2进制编码树，代编码符号数量5
		cout << endl << "**********5个待编码符号，2进制霍夫曼编码***********" << endl;
		Huffman_CodingTree Huf(2); // 建立编码树
		StringSeque a(5); // 定长概率序列发生器

		auto x = a.get_NewSequece(); // 生成序列
		for (unsigned int i = 0; i < x.size(); i++)
		{
			Huf.add_Node(x[i].content, x[i].probility); // 向编码树压入待编码序列
		}

		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率

		cout << endl << "**********8个待编码符号，2进制霍夫曼编码***********" << endl;
		a.change_length(8); // 改变概率序列发生器长度
		x = a.get_NewSequece(); // 产生新的序列
		Huf.clear_all_Node(); // 清除已有节点
		for (unsigned int i = 0; i < x.size(); i++)
		{
			Huf.add_Node(x[i].content, x[i].probility); // 向编码树压入新的待编码序列
		}

		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率

		cout << endl << "**********17个待编码符号，2进制霍夫曼编码***********" << endl;
		a.change_length(17); // 改变概率序列发生器长度
		x = a.get_NewSequece(); // 产生新的序列
		Huf.clear_all_Node(); // 清除已有节点
		for (unsigned int i = 0; i < x.size(); i++)
		{
			Huf.add_Node(x[i].content, x[i].probility); // 向编码树压入新的待编码序列
		}

		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率
	}

	//演示4进制下，固定数量的不同序列的编码效果
	cout << endl << "**********以下演示4进制霍夫曼编码下，固定个数的不同待编码符号的编码结果***********" << endl;
	{
		// 建立4进制编码树，代编码符号数量12
		cout << endl << "**********12个待编码符号，4进制霍夫曼编码***********" << endl;
		Huffman_CodingTree Huf(4); // 建立编码树
		StringSeque a(12); // 定长概率序列发生器

		auto x = a.get_NewSequece(); // 生成序列
		for (unsigned int i = 0; i < x.size(); i++)
		{
			Huf.add_Node(x[i].content, x[i].probility); // 向编码树压入待编码序列
		}

		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率

		cout << endl << "**********12个待编码的新符号符号***********" << endl;
		x = a.get_NewSequece(); // 产生新的序列
		Huf.clear_all_Node(); // 清除已有节点
		for (unsigned int i = 0; i < x.size(); i++)
		{
			Huf.add_Node(x[i].content, x[i].probility); // 向编码树压入新的待编码序列
		}

		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率

		cout << endl << "**********12个待编码的新符号符号***********" << endl;
		x = a.get_NewSequece(); // 产生新的序列
		Huf.clear_all_Node(); // 清除已有节点
		for (unsigned int i = 0; i < x.size(); i++)
		{
			Huf.add_Node(x[i].content, x[i].probility); // 向编码树压入新的待编码序列
		}

		Huf.start_coding(); // 开始编码
		Huf.output_coding(); // 打印字符串对应的编码
		Huf.output_para(); // 打印熵、平均码长和编码效率
	}
	return 0;
}