#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include"Huffman_Coding.h"

using namespace std;

int main(void) {
	Huffman_CodingTree Huf(2); // 建立2进制编码树
	Huf.add_Node("a", 0.3); // a字符概率为0.3
	Huf.add_Node("b", 0.2); // b字符概率为0.2
	Huf.add_Node("c", 0.25); // c字符概率为0.25
	Huf.add_Node("d", 0.13); // d字符概率为0.13
	Huf.add_Node("e", 0.12); // e字符概率为0.12
	Huf.start_coding(); // 开始编码
	Huf.output_coding(); // 打印字符串对应的编码
	Huf.output_para(); // 打印熵、平均码长和编码效率
	return 0;
}