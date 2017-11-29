#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	ifstream natfile("./nat.txt");
	ifstream flowfile("./flow.txt");
	ofstream outf("./output.txt");
	string nat_data;
	string flow_data;
	int pos  = -1;
	bool flag = false;
	while (getline(flowfile, flow_data)) {
		while (1) {
			if(!getline(natfile, nat_data))
				break;
			// compare the two strings
			// check if flow_data is substring of nat_data
			if(nat_data.find(flow_data) != string::npos){
				outf <<flow_data<<" -> "<<nat_data.substr(nat_data.find(",")+1,string::npos)<<endl;
					flag = true;
		}
			else if((pos = nat_data.find("*")) != string::npos) {
				if (pos == 0) { // ip address is star we have to compare only port number
					// copy from 1 till ,
					int com = nat_data.find(',');
					string port_st = nat_data.substr(pos+1,com-1);
					if((pos = flow_data.find(port_st)) != string::npos){
						outf <<flow_data<<" -> "<<nat_data.substr(nat_data.find(",")+1,string::npos)<<endl;
					flag = true;
					}
				}

				else { // port number is star we have to compare only ip address
					// copy from : till ,
					int col = nat_data.find(':');
					string ip_st = nat_data.substr(0,pos-1);
					if((pos = flow_data.find(ip_st)) != string::npos){
						outf <<flow_data<<" -> "<<nat_data.substr(nat_data.find(",")+1,string::npos)<<endl;
					flag = true;
					}
				}
			}
		}
		if(!flag)
				outf<<"No nat match for "<<flow_data<<endl;
		flag = false;
		//set file position to the begining
		natfile.clear();
		natfile.seekg(0,natfile.beg);
	}
	return 0;
}
