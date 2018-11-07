#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class PostFix {
private:
	stack<char> pile;
	vector<char> tabPostFix;
public:
	string transformerEnPostFix(string expression);
	bool estUneValeur(char c);
	int poidsOperateur(char c);
};

int PostFix::poidsOperateur(char c) {
	int poids = -1;
	if (c == '+' || c == '-')
		poids = 1;
	else if (c == '*' || c == '/' || c == '%')
		poids = 2;
	return poids;
}

bool PostFix::estUneValeur(char c) {
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

string PostFix::transformerEnPostFix(string expression) {
	
	char temp;

	string postfix = "";
	for (int i = 0; i < expression.length(); i++) {

		if (poidsOperateur(expression[i]) != -1)
		{
			while (!pile.empty() && pile.top() != '(' && poidsOperateur(pile.top() <= poidsOperateur(expression[i])))
			{
				postfix += pile.top();
				pile.pop();
			}
			pile.push(expression[i]);
		}
		else if (estUneValeur(expression[i]))
		{
			postfix += expression[i];
		}
		else if (expression[i] == '(')
		{
			pile.push(expression[i]);
		}
		else if (expression[i] == ')')
		{
			while (!pile.empty() && pile.top() != '(')
			{
				postfix += pile.top();
				pile.pop();
			}
			pile.pop();
		}

	}
	while (!pile.empty())
	{
		postfix += pile.top();
		pile.pop();
	}

	return postfix;
}


int main() {
	string expression;
	cout << "Entrez l'expression infixe à transformer en postfix: " << endl;
	cin >> expression;

	PostFix post;
	cout << "\nExpression PostFix: " << post.transformerEnPostFix(expression) << endl;
	
	system("PAUSE");
	return 1;
}