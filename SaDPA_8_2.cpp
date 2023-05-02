#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
using namespace std;
pair<vector<vector<int>>, vector<map<char, int>>> boyer_moore(vector<string> patterns, string text) {
	vector<map<char, int>> all_shifts; //вектор хеш-таблиц
	vector<vector<int>> all_pos; //вектор векторов вхождений
	int Cf = 0, Mf = 0;
	for (int i = 0; i < patterns.size(); i++) {
		map<char, int> shifts; //хеш-таблица сдвига для текущего шаблона
		vector<int> pos; //вектор вхождений
		for (int j = 0; j < patterns[i].size(); j++) {
			if (shifts.find(patterns[i][j]) == shifts.end()) {
				shifts.insert(pair<char, int>(patterns[i][j], 0));
			}
		}
		for (int j = patterns[i].size() - 2; j >= 0; j--) {
			if (shifts.find(patterns[i][j])->second == 0) {
				shifts.find(patterns[i][j])->second = patterns[i].size() - j - 1;
			}
			else {
				break;
			}
		}
		int curr_shift = 0, flag = 0;
		while (curr_shift + patterns[i].size() < text.size()) {
			for (int j = patterns[i].size() - 1; j >= 0; j--) {
				Cf++;
				if (text[j + curr_shift] != patterns[i][j]) {
					Cf++;
					if (shifts.find(text[j + curr_shift]) == shifts.end()) {
						Mf++;
						curr_shift += patterns[i].size();
					}
					else {
						Cf++;
						if (shifts.find(text[j + curr_shift])->second != 0) {
							Mf++;
							curr_shift += shifts.find(text[j + curr_shift])->second;
						}
						else {
							Mf++;
							curr_shift++;
						}
					}
					flag = 1;
					break;
				}
			}
			if (flag != 1) {
				pos.push_back(curr_shift);
				Mf++;
				curr_shift++;
				flag = 0;
			}
			flag = 0;
		}
		cout << Cf << "+" << Mf;
		all_shifts.push_back(shifts);
		all_pos.push_back(pos);
	}
	return pair<vector<vector<int>>, vector<map<char, int>>>(all_pos, all_shifts);
}
int main() {
	string text = "hello my name is wafle and i am an ai language model created by openai i am designed to generate human-like text based on the input i receive from users i am constantly learning and improving my language skills through machine learning algorithms i can write on a variety of topics such as science technology history and more my purpose is to assist users in generating high-quality content quickly and efficiently if you have any questions or suggestions for me feel free to ask i am here to help you in any way i can thank you for using my services";
	vector<string> pattern = { "using" };
	pair<vector<vector<int>>, vector<map<char, int>>> result;
	auto start = chrono::high_resolution_clock::now();
	result = boyer_moore(pattern, text);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Time: " << duration.count() << " nanoseconds" << endl;
	for (int i = 0; i < 1; i++) {
		cout << "for pattern " << pattern[i] << " shifts are: ";
		for (auto j : result.second[i]) {
			cout << "\"" << j.first << "\" - " << j.second<<", ";
		}
		cout << endl;
		cout << "were it is spotted: ";
		for (int j : result.first[i]) {
			cout << j << " postion, ";
		}
		cout << endl;
	}
}