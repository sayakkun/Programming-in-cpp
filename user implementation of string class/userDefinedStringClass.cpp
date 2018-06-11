#include<bits/stdc++.h>
using namespace std;
class myString
{
    private:
        char *str;
        int curr_str_size;
        int curr_position;
    public:
        myString();
        myString(char *str);
        myString(const myString &);
        myString& operator=(const myString &);
        myString& operator=(const char *);
        friend ostream& operator<<(ostream &,const myString &);
 //it will return a reference to the ostream(output stream) and it is overriding <<. 
        //it cannot be part of this
        //hence, friend function
        //subscript operator overloading:
        //gives direct access to the ith character of a string
        char operator[](int);
        int length();
        void push_back(char);
        char pop_back();
};
myString::myString()
{
    //if no size is specified
    //one default size can be given 
    //let's suppose that default size is 32
    cout<<"Default constructor is called"<<endl;
    try
    {
        str=new char[32];
        curr_str_size=32;
        curr_position=0;
    }
    catch(bad_alloc e)
    {
        throw ("Further string can not be created. As further heap memory cannpot be allocated");
    }
    
}
myString::myString(char *str)
{
    cout<<"parametric constructor is called"<<endl;
    if(str==NULL)
    {
        throw ("The str which is passed as argument to this function is NULL");
    }
    //however, it does not handle if the str is not null terminated
    this->curr_str_size=strlen(str)+1;
    this->curr_position=strlen(str);
    this->str=new char[this->curr_str_size];
    strcpy(this->str,str);
}
myString::myString(const myString &myStr)
{
    cout<<"Copy constructor is called"<<endl;
    //self reference checking
    if(this==&myStr)
    {
        return;
        
    }
    //why const reference sending is important
    //const because, we need not the argument to be modified
    //reference because, otherwise copy constructor will be invoked for the argument itself
    //delete str;
    //here, you cannot delete it, because, it is an uninitialized pointer 
    //uninitialized pointer derefenecning or deleting can cause segmentation fault
    //hence, this will does not cause segmentation fault
    
    this->curr_str_size=strlen(myStr.str)+1;
    this->curr_position=strlen(myStr.str);
    str=new char[this->curr_str_size];
    strcpy(str,myStr.str);
    
    //in copy constructor, we can access other object's private member. But, the object
    //should be of same class
}
//assignment operator overloading
myString& myString::operator=(const myString &myStr)
{
    //self reference checking
    cout<<"Assignment operator is overloaded"<<endl;
    if(this==&myStr)
    {
        return *this;
    }
    delete str;
    //it was never initialized to null 
    //hence, this will does not cause segmentation fault
    /*Important for this kind of stupid operation we do every day
    myString str;
    str="Sayak Haldar";
    */
    this->curr_str_size=strlen(myStr.str)+1;
    str=new char[this->curr_position];
    strcpy(str,myStr.str);
    return *this;
}
myString& myString::operator=(const char* str)
{
    cout<<"Assignment operator is overloaded"<<endl;
//no need to self reference checking
//because, it is not accepting a string as an argument. Rather, it will accept a const char as an argument
    delete this->str;
    this->curr_position=strlen(str);
    this->curr_str_size=this->curr_position;
    strcpy(this->str,str);
    return *this;
}
char myString::operator[](int index)
{
    if(index<0||index>=curr_position)
    {
        throw ("Index out of bound exception");
    }
    return str[index];
}
int myString::length()
{
    return this->curr_position;
}
void myString::push_back(char c)
{
    if(this->curr_position+1>=this->curr_str_size)
    {
        //we need to realloc
        char *tempStr=new char[this->curr_str_size+1];
        strcpy(tempStr,str);
        delete str;
        //now, tempStr is not a pointer alias
        //hence, it will remain fine even if we delete str
        str=new char[this->curr_str_size+1+32];
        //allocating some extra space to make push_back operation little less time consuming
        this->curr_str_size=this->curr_str_size+32;
        strcpy(str,tempStr);
        str[this->curr_position]=c;
        str[this->curr_position+1]='\0';
        //very important, otherwise it wont be null terminated
        this->curr_position=this->curr_position+1;
        delete tempStr;
        //otherwise, there will be a memory leak
    }
    //now, it good for checking 
    //however, we still need to remember that curr_position is in 1 indexing
    else
    {
        str[this->curr_position]=c;
        str[this->curr_position+1]='\0';
        this->curr_position=this->curr_position+1;
    }
}
char myString::pop_back()
{
    char c=str[curr_position-1];
    //remember it is a null terminated string and curr_postion is in 1 indexing
    //hence,str[curr_position] will actually contain '\0';
    str[curr_position-1]='\0';
    return c;
}
ostream& operator<<(ostream &os,const myString &myStr)
{
    return os<<myStr.str;
}
int main()
{
    myString str1;
    //this will invoke default constructor
    str1="Sayak Haldar";
    //this will invoke assginment operator
    cout<<str1<<endl;
    myString str2("Surekha Haldar");
    //this will invoke parametric constructor
    cout<<str2<<endl;
    myString str3(str2);
    //this will invoke copy constructor
    cout<<str3<<endl;
    myString str4;
    str4=str1;
    //this will invoke assignment operator 
    cout<<str4<<endl;
}
