#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
	T *a;
	int size;
    void double_space()
    {
        T *b=new T[2*size];
        for(int i=0;i<size;++i)
            b[i]=a[i];
        delete []a;
        a=b;
        size*=2;
    }

    void quicksort(T a[],int start,int end)
    {
        if (start<end)
        {
            int k=a[start];
            int i=start,j=end;
            while (i<j)
            {
                while (i<j&&a[j]>=k) --j;
                if (i<j) {a[i]=a[j];++i;}
                while (i<j&&a[i]<=k) ++i;
                if (i<j) {a[j]=a[i];--j;}
            }
            a[i]=k;
            quicksort(a,start,i-1);
            quicksort(a,i+1,end);
        }
    }

public:
    MyList(){
		size=0;
		a=new T[100];
	}

    MyList(int num, const T &item)
    {
        try{
            if(num<0) throw num;
            a=new T[num];
            for(int i=0;i<num;++i)
                a[i]=item;
            size=num;
            }
        catch(int) {size=0;a=new T[100];cout<<"Error! the size of the array can't be less than or equal to 0"<<endl;}
    }


    MyList(const MyList &l)
    {
        a=new T[l.size];
        for(int i=0;i<l.size;++i)
            a[i]=*(l.a+i);
        size=l.size;
    }

    MyList(T* arr, int len)
    {
        try
        {
            if(len<0||len>sizeof(arr)/sizeof(T)) throw len;
            a=new T[len];
            for(int i=0;i<len;++i)
            {
                a[i]=arr[i];
            }
            size=len;
        }
    catch(int) {size=0;a=new T[100];cout<<"Error!length is greater than the size of array"<<endl;}

    }

    void push(const T &item)
    {
        double_space();
        size=size/2+1;
        a[size-1]=item;
}


    T pop()
    {
        try
        {
            if(size==0) throw size;
            T *b=new T[size-1];
            for(int i=0;i<size-1;++i)
                b[i]=a[i];
            T temp=a[size-1];
            delete []a;
            a=b;
            --size;
            //or simply --size;
            return temp;
        }
        catch(int) {cout<<"null array!"<<endl;return a[0];}
    }



    void insert(int index, const T &item)
    {
        try
        {
            if(index<0) index+=size;
            if(index>=size||index<0) throw index;
            ++size;
            T *b=new T[size];
            for(int i=0;i<index;++i)
                b[i]=a[i];
            b[index]=item;
            for(int i=index+1;i<size;++i)
                b[i]=a[i-1];
            delete []a;
            a=b;
        }
        catch(int) {cout<<"beyond size!"<<endl;}
    }


    void clean()
    {
        //a=new T[size];
        size=0;
    }

    int get_size()
    {
        return size;
    }


    void erase(int start, int end)
    {
        try{
            if(start<0) start+=size;
            if(end<0) end+=size;
            if (start >= size || end >= size||start > end||start<0||end<0) throw 0;
            size -= (end - start + 1);
            T *b = new T [size];
            for (int i = 0;i < start;++i) b[i] = a[i];
            for (int i = start;i < size;++i) b[i] = a[i + end - start + 1];
            delete [] a;
            a = b;
        }
        catch (int){
            cout << "Error! beyond size!" << endl;
        }

    }


    T get_item(int index)
    {
        try
        {
            if(index<0) index+=size;
            if(index>=size||index<0) throw index;
            return a[index];
        }
        catch(int) {cout<<"beyond size!"<<endl;return a[0];}
    }



    MyList get_item(int start, int end)
    {
        MyList<T> b;
        try
        {
            if(start<0) start=size+start;
            if(end<0) end=size+end;
            if(start>=size||end>=size||start<0||end<0) throw size;

            if(start>end)  {b.clean();}
            else
            {
                int j=0;
                for(int i=start;i<=end;++i)
                {
                    b.a[j]=a[i];
                    ++j;
                }
                b.size=end-start+1;
            }

        }
        catch(int) {cout<<"beyond size!"<<endl;b.clean();}
        return b;
    }


    int count(const T &item)
    {
        int sum=0;
        for(int i=0;i<size;++i)
        {
            if(a[i]==item) ++sum;
        }
        return sum;
    }

    void remove(const T &item)
    {
        for(int i=0;i<size;++i)
        {
            if(a[i]==item)
            {
                erase(i,i);
                break;
            }
        }
    }


   friend MyList operator + (const MyList &l1, const MyList &l2){
        MyList<T> result = l1;
        int total = l1.size+l2.size;
        while (result.size < total) result.double_space();
        for (int i = 0;i < l2.size;++i) {
            result.a[i+l1.size] = l2.a[i];
        }
        return result;
    }

    friend MyList operator + (const MyList &l1, const T &item){
        MyList<T> result = l1;
        result.push(item);
        return result;
    }

    MyList &operator = (const MyList &l)
    {
        if(this==&l) return *this;
        delete []a;
        size=l.size;
        a=new T[size];
        for(int i=0;i<size;++i)
            a[i]=l.a[i];
        return *this;
    }

    MyList &operator += (const T &item)
    {
        push(item);
        return *this;
    }

    MyList &operator += (const MyList &l)
    {
        for(int i=0;i<l.size;++i)
            push(l.a[i]);
        return *this;
    }


    T &operator [](int index)
    {
        try
        {
            if(index<0) index+=size;
            if(index>=size||index<0) throw index;
            return a[index];
        }
        catch(int) {cout<<"beyond size!"<<endl;return a[0];}
    }



    friend ostream & operator<<(ostream &os, const MyList &obj)
    {
        os<<'[';
        for(int i=0;i<obj.size;++i)
        {
            if(i!=obj.size-1) os<<obj.a[i]<<", ";
            else os<<obj.a[i];
        }
        os<<']';
        return os;
    }


    void reverse()
    {
        T *b=new T[size];
        for(int i=0;i<size;++i)
            b[size-1-i]=a[i];
        delete []a;
        a=b;
    }


    void sort(bool less=true)
    {
        try
        {
            if(size==0) throw 0;
            quicksort(a,0,size-1);
            if(less){}
            else
            {
                reverse();
            }
        }
        catch(int) {cout<<"No element!Null MyList!"<<endl;}
    }

    ~MyList() {delete []a;}
};

int main(){
    MyList<int> a, b;
    int i;
    for (i=0; i<5; ++i)
        a.push(i);
    // a = [0, 1, 2, 3, 4]
    a[3] = 15; // a = [0, 1, 2, 15, 4]
    a.sort(); // a = [0, 1, 2, 4, 15]
    a.reverse(); // a = [15, 4, 2, 1, 0]
    a += 12; // a = [15, 4, 2, 1, 0, 12]
    for (i=0; i<a.get_size(); ++i)
        cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *Èôstart > end£¬·µ»Ø¿ÕÊý×é
    b = a.get_item(3, -1); // b = [1, 0, 12]
    a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
    for (i=0; i<a.get_size(); ++i)
        cout<<a.get_item(i)<<endl;
    cout<<a.count(5)<<endl;
    b.clean(); // b = []
    cout<<b.get_size()<<endl;
    a.erase(2, 5); // a = [15, 4, 0,1, 12]
    b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
    b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
    b.remove(4); // b = [15, 0, 116, ...]
    cout<<b<<endl;
    MyList<double> c(0, 3.14);
    for (i=0; i<100; ++i)
        c.push(1.1*i);
    cout<<c.get_item(100, 105)<<endl;

    return 0;
}
