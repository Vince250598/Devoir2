#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class PostFix {
private:
	stack<char> pile;
	vector<string> tabPostFix;
	stack<string> pileCalcul;
public:
	string transformerEnPostFix(string expression);
	bool estUneValeur(char c);
	int poidsOperateur(char c);
	string evaluerExpressionPostFix(string expression);
	int evaluerOperation(int valeur1, int valeur2, char operateur);
};

int PostFix::evaluerOperation(int valeur1, int valeur2, char operateur) {
	int resultat;

	switch (operateur)
	{
	case '+':
		resultat = valeur1 + valeur2;
		break;
	case '-' :
		resultat = valeur1 - valeur2;
		break;
	case '*' :
		resultat = valeur1 * valeur2;
		break;
	case '/':
		resultat = valeur1 / valeur2;
		break;
	case '%':
		resultat = valeur1 % valeur2;
		break;
	default:
		break;
	}
	return resultat;
}

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
	int j = 0;
	string element = "";

	for (int i = 0; i < expression.length(); i++) //ne pas utiliser cin
	{
		if (expression[i] == ' ')
		{
			j++;
		}
		else if(expression[i + 1] == ' ')
		{
			element += expression[i];
			tabPostFix[j] = element;
		}
		else
		{
			element += expression[i];
		}
	}

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

string PostFix::evaluerExpressionPostFix(string expression) {
	string resultat;
	char operateur;
	int valeur1;
	int valeur2;

	for (int i = 0; i < expression.length(); i++)
	{
		if (estUneValeur(expression[i])) {
			string s(1, expression[i]);
			pileCalcul.push(s);
		}
		else if (poidsOperateur(expression[i]) != -1)
		{
			valeur1 = stoi(pileCalcul.top());
			pileCalcul.pop();
			valeur2 = stoi(pileCalcul.top());
			pileCalcul.pop();
			string res = to_string(evaluerOperation(valeur2, valeur1, expression[i]));
			pileCalcul.push(res);
		}

	}

	resultat = pileCalcul.top();
	return resultat;
}

int main() {
	string expression;
	cout << "Entrez l'expression infixe à transformer en postfix: " << endl;
	cin >> expression;

	PostFix post;
	string expressionPost = post.transformerEnPostFix(expression);
	cout << "\nExpression PostFix: " << expressionPost << endl;

	cout << "\nResultat PostFix: " << post.evaluerExpressionPostFix(expressionPost) << endl << endl;
	
	system("PAUSE");
	return 1;
}