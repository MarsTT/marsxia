#include<iostream>
#include<vector>

using namespace std;

class PackEnum
{
protected:
	vector<int> m_p; //N�������ļ۸�
	vector<int> m_w;// N������������
	int m_c;        //����������
	int m_num;      //��Ʒ�ļ���


public:
	PackEnum();  //���캯��
	PackEnum(vector<int>& p,vector<int>& w,int c,int n):m_p(p),m_w(c),m_c(c),m_num(n){}//���캯����ʼ������ֵ

	//��ȡ��������Ʒ�����ֵ
	int GetBestValue() const{
		int bestValue=0;           //��������ֵ
		int currentValue=0;       //��ǰ��������Ʒ�ļ�ֵ
		int currentWeight=0;      //��ǰ��������Ʒ������ 

		const unsigned int max = 2 << m_num;
		//������еĿ���
		for(unsigned int i=0;i<max;++i){
			//��ձ���
			currentValue = 0;
			currentWeight = 0;
			//ȡ�������е�ÿһλ
			unsigned int bit = i;
			int j=0;
			while(bit!=0){
				currentWeight+=m_w[j]*(bit & 1);
				currentValue+=m_p[j]*(bit & 1);
				//���bit�����λΪ1����bit&1=1������Ϊ0
				bit >>= 1;
				++j;
			}
			//�������Ž�
			if(currentWeight<=m_c && bestValue < currentValue){
				bestValue = currentValue;
			}
		}
		return bestValue;
	}
};


int main03(void){
	int n;
	int c;

	cout << "��������Ʒ�ļ��� :" <<endl;
	cin >> n;
	cout << "�����뱳�������� :"<<endl;
	cin>>c;
	vector<int> w(n);
	vector<int> p(n);

	cout<<"��������Ʒ������ :"<<endl;
	for(int i=0;i<n;++i){
		cin >>w[i];
	cout<<"��������Ʒ�ļ�ֵ:"<<endl;
	for(int j=0;j<n;j++)
		cin>>p[j];

	PackEnum pack(p,w,c,n);

	int bestValue = pack.GetBestValue();
	cout<<"��������Ʒ������ֵΪ��" <<bestValue<<endl;
	return 0;
	}

}