#include<bits/stdc++.h>
using namespace std;

// precedence of operators
int prec(char c) {
    if(c=='^')
        return 3;
    else if(c=='/' || c=='*')
        return 2;
    else if(c=='+' || c=='-')
        return 1;
    else
        return -1;
}

char associativity(char c) {
    if(c=='^')
        return 'R'; // since '^' is right associative, it would have higher precedence when scanned than being on top of stack
    return 'L';
}

void inf_to_post(string s) {
    stack<char> st;
    string result;

    for(int i=0; i<s.length(); i++) {
        char c=s[i];
        // if operand occurs
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9')) {
            result+=c;
        }
        // occurrence of open parentheses
        else if(c=='(') {
            st.push(c);
        }
        // when ')' occurs, pop the stack and put it into result until we get '('
        else if(c==')') {
            while(st.top()!='(') {
                result+=st.top();
                st.pop();
            }
            st.pop();
        }
        // when operator occurs
        else {
            while(!st.empty() && (prec(c)<prec(st.top()) || prec(c)==prec(st.top())&& associativity(c)=='L')) {
                result+=st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.empty()) {
        result+=st.top();
        st.pop();
    }

    cout<<"The postfix expression is "<<result<<endl;
}

int main() {
    string exp = "(a+b)*c/d-e^f^g/h";
    cout << "Infix expression: " << exp << endl;
    inf_to_post(exp);
    return 0;
}
