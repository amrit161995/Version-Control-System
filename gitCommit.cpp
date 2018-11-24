#include<stdio.h>
#include<string>
#include <openssl/sha.h>
#include "generateSHA.cpp"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;

class Commit
{
    public:
        char type[10]="commit";
        char tree[60]= "";
        char parent[60]="";
        char author[200]="";
        char committer[200]="";
        char message[500]="";
        char * content;

        void Print_Type()
        {
            cout<<type<<endl;
        }

        void Print_Content()
        {
            cout<<"tree : "<<tree<<endl;
            // cout<<"parent : "<<parent<<endl;
            cout<<"author : "<<author<<endl;
            cout<<"committer : "<<committer<<endl;
            cout<<endl;
            cout<<message<<endl;
        }

        void setContent(char *con){
            content=con;
        }

        char * getContent(){
            return content;
        }

  



string createCommit(string tree,string parent,string author,string committer,string message)
{   
    strcpy(this->tree,tree.c_str());
    strcpy(this->parent,parent.c_str());
    strcpy(this->author,author.c_str());
    strcpy(this->committer,committer.c_str());
    strcpy(this->message,message.c_str());
    string temp="tree : "+tree+";"+"parent : "+parent+";"+"author : "+author+";"+"committer : "+committer+";"+"message : "+message+";";
    char* t = new char[temp.length()];
    content = t;
    // string temp=string(bytes.data(), fileSize);
     strcpy(content,temp.c_str());
    // setContent(content);
    // type="blob";
     string type1=this->type;
     
    string header=type1+" "+to_string(temp.length())+"\0";

    string store = header+ " " + temp;
    string sha1=generateSHAstring(store);

    return sha1;
}


};

void serializeCommit(string tree,string parent,string author,string committer,string message){
    //cout<<"hello";
    Commit com;
    string hash_filename=com.createCommit(tree,parent,author,committer,message);

    string directory="";
    string commitname="";
    for(int i=0;i<2;i++)
        directory+=hash_filename[i];
    mkdir((".mygit/objects/"+directory).c_str(),0777);
     cout<<directory<<endl;

    for(int i=2;i<40;i++)
        commitname+=hash_filename[i];

     cout<<commitname<<endl;
    // cout<<hash_filename;
    FILE *File = fopen((".mygit/objects/"+directory+"/"+commitname).c_str(),"wb");
    // Test.Print_Content();
    // cout<<Test.getContent();
    fwrite((char *)&com,sizeof(com),1,File); //Treats the object as if it is a char array
    fclose(File);

    
}


void deserializeCommit(string file){
     Commit com;
     FILE *File;

     string directory="";
     string commitname="";

     for(int i=0;i<2;i++)
        directory+=file[i];
    // mkdir(".git/objects/"+directory);
    // cout<<directory<<endl;

    for(int i=2;i<40;i++)
        commitname+=file[i];
     string path=".mygit/objects/"+directory+"/"+commitname;
    File = fopen(path.c_str(),"rb");
    fread((char *)&com,sizeof(com),1,File); //Treats the object as if it is a char array
    com.Print_Content();
    fclose(File);

 }


 int main(){
    // string fileName="abc.txt";
    serializeCommit("asd132qdads","asddas","amrit","amrit","initial commit");

    string hash;
    cout<<"enter hash: ";
    cin>>hash;
    deserializeCommit(hash);
    return 0;
}