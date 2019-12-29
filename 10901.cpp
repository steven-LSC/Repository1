#include <iostream>
#include <string>
#include <queue>
#include<map>
#include<vector>
using namespace std;

int main() {
	int cases, ferryCapacity, crossTime, numberOfCar, temp;
	cin >> cases;
	while (cases--) {

		cin >> ferryCapacity >> crossTime >> numberOfCar;

		bool position = 0;
		vector<queue<int>> port;
		queue<int> leftport;
		queue<int> rightport;
		port.push_back(leftport);
		port.push_back(rightport);
		
		queue<pair<int, bool>> information;
		queue<int> ferry;
		//�˧�->�R��->�ﭱ
		for (int i = 0; i < numberOfCar; i++) {
			string stemp;
			cin >> temp >> stemp;
			pair<int, bool> pTemp(temp, stemp == "right");
			information.push(pTemp);
		}
		int time = 0, number = 0;
		multimap<int, int> dictionary;
		while (true)
		{
			//���ŴN����
			if (information.empty() && port[0].empty() && port[1].empty() && ferry.empty()) {
				break;
			}
			//����Ӵ�f���O�Ū�
			if (ferry.empty() && port[0].empty() && port[1].empty()) {
				//�B�z�� �U�@�B�O�e��ت��a
				if (information.front().second == position) {
					time = information.front().first;
					port[position].push(number++);
					information.pop();
				}
				else {
					time = information.front().first;
					time += crossTime;
					position = !position;
					port[position].push(number++);
					information.pop();
				}
			}
			//����Ӵ�f�u�n���@�ӨS�ŴN�B�@
			else {
				//����
				while (!ferry.empty())
				{
					dictionary.insert(pair<int, int>(ferry.front(), time));//���l���|�H�۽s���U�� �]��map�i�H��������
					ferry.pop();										   //�s���Ʀn�A�ðO�����ӽs���U��ɶ��I
				}
				//������W
				for (int i = 0; i < ferryCapacity; i++)
				{
					if (!port[position].empty()) {
						ferry.push(port[position].front());
						port[position].pop();	
					}
					else {
						break;
					}
				}
				//���i�ਮ��U�� ��f�S�� ���N���n�� ��U��䤤�@�Ӧ������N���t�@�䨫
				if (!ferry.empty() || !port[0].empty() || !port[1].empty()) {
					position = !position;
					time += crossTime;
				}
			}
			//�C��@���e ���n�T�{�O�_�ɶ��w�g��F�n�[�J�s�����l
			while (!information.empty() && time >= information.front().first) {
				port[information.front().second].push(number++);
				information.pop();
			}
		}
		for (multimap<int, int>::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
			cout << it->second << endl;
		}
		if (cases != 0) {
			cout << endl;
		}
	}
	return 0;
}