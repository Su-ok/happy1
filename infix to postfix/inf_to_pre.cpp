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

/* char associativity(char c) {
    if(c=='^')
        return 'R';
    return 'L';
} */

// infix to postfix conversion
string inf_to_post(string s) {
    stack<char> st;
    string result;

    for(int i=0; i<s.length(); i++) {
        char c=s[i];

        // if operand is there
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
            st.pop(); // pop '('
        }
        // when operator occurs
        else {
            if(c=='^') {
                while(!st.empty() && prec(c)<=prec(st.top())) {
                    result+=st.top();
                    st.pop();
                }
            }
            else {
                while(!st.empty() && prec(c)<prec(st.top())) {
                    result+=st.top();
                    st.pop();
                }
            }
            st.push(c);
        }
    }

    while(!st.empty()) {
        result+=st.top();
        st.pop();
    }

    return result;
}

string inf_to_pre(string s) {
    int l=s.length();

    reverse(s.begin(),s.end());

    for(int i=0; i<l; i++) {
        if(s[i]=='(')
            s[i]=')';
        else if(s[i]==')')
            s[i]='(';
    }
    string prefix=inf_to_post(s);

    reverse(prefix.begin(),prefix.end());

    return prefix;
}
int main() {
    string exp = "(a+b)*c/d-e^f^g/h";
    cout << "Infix expression: " << exp << endl;
    cout<<"Prefix expression: "<<inf_to_pre(exp)<<endl;
    return 0;
}
