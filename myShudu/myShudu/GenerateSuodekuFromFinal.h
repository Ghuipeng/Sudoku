//�Ӽ����վ��л�ȡ����
//num��ʾ��ȡ������������
//oneSolution��ʾ�Ƿ��ȡֻ��һ���������
//diffcult ��ʾ�Ѷȣ��Ѷ������������棬һ���ڿյ���Ŀ��һ����ÿ���հ׵����ɶ�
//low��high���޶����ڿյ�������ȫ������0��ʾ��������Ϊ�޶�
const int low_limit = 20;
const int high_limit = 55;
const int low_freedom = 400;
const int high_freedom = 1100;
void Generate(int num, bool oneSolution = false, int diffcult = 0, int low = 20, int high = 55);

//���ѶȺ��ڿ����ƻ���ڿյ�λ��
//����ֵ��place�ĳ���
//place����һ��ָ��
//��������ɵõ�һ��place���飬���ж��Ƿ�����Ѷ�
//place��һ��һά���飬����0��2��3��ʾ��0��2��3λ���ڿգ�����õ��ڶ�ά�����е�λ��
int GetBlankPlace(int* place, int diffcult = 0, int low = 20, int high = 55);

//���plcae���Ѷ�
int GetDiffcult(int* place, int length);

//������ڿ����õ����Ѷ�
float GetNumDiff(int length);

//�����ά����Ϊ����������
//��������ɶȵõ����Ѷ�
float GetFreeDiff(int** place);
int GetFree(int** place, int x, int y);