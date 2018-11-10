#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class PostFix {
private:
	stack<string> pile;
	vector<string> tabPreFix;
	vector<string> tabPostFix;
	stack<string> pileCalcul;
	string postFix = "";
public:
	void transformerEnPostFix(string expression);
	bool estUneValeur(string c);
	int poidsOperateur(string c);
	string evaluerExpressionPostFix();
	int evaluerOperation(int valeur1, int valeur2, char operateur);
	void evaluation();
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

int PostFix::poidsOperateur(string c) {
	int poids = -1;
	if (c.length() > 1)
	{
		return poids;
	}
	if (c.at(0) == '+' || c.at(0) == '-')
		poids = 1;
	else if (c.at(0) == '*' || c.at(0) == '/' || c.at(0) == '%')
		poids = 2;
	return poids;
}

bool PostFix::estUneValeur(string c) {
	for (int i = 0; i < c.length(); i++)
	{
		if (c.at(i) > 57 || c.at(i) < 48) {
			return false;
		}
	}
	return true;
}

void PostFix::transformerEnPostFix(string expression) {
	int j = 0;
	string element = "";

	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == ' ')
		{
			element = "";
			continue;
		}
		else if(expression[i + 1] == ' ')
		{
			element += expression[i];
			tabPreFix.insert(tabPreFix.begin() + j, element);
			j++;
		}
		else if(i == (expression.length()-1))
		{
			element += expression[i];
			tabPreFix.insert(tabPreFix.begin() + j, element);
		}
		else
		{
			element += expression[i];
		}
	}

	string temp;
	j = 0;

	for (int i = 0; i < tabPreFix.size(); i++) {

		if (poidsOperateur(tabPreFix.at(i)) != -1)
		{
			while (!pile.empty() && pile.top().at(0) != '(' && poidsOperateur(pile.top()) <= poidsOperateur(tabPreFix.at(i)))
			{
				tabPostFix.insert(tabPostFix.begin() + j, pile.top());
				pile.pop();
				j++;
			}
			pile.push(tabPreFix.at(i));
		}
		else if (estUneValeur(tabPreFix.at(i)))
		{
			tabPostFix.insert(tabPostFix.begin() + j, tabPreFix.at(i));
			j++;
		}
		else if (tabPreFix.at(i)[0] == '(')
		{
			pile.push(tabPreFix.at(i));
		}
		else if (tabPreFix.at(i)[0] == ')')
		{
			while (!pile.empty() && pile.top().at(0) != '(')
			{
				tabPostFix.insert(tabPostFix.begin() + j, pile.top());
				j++;
				pile.pop();
			}
			pile.pop();
		}

	}
	while (!pile.empty())
	{
		tabPostFix.insert(tabPostFix.begin() + j, pile.top());
		j++;
		pile.pop();
	}

	for (int i = 0; i < tabPostFix.size(); i++)
	{
		postFix += tabPostFix.at(i);
	}
}

string PostFix::evaluerExpressionPostFix() {
	string resultat;
	string operateur;
	int valeur1;
	int valeur2;

	for (int i = 0; i < tabPostFix.size(); i++)
	{
		if (estUneValeur(tabPostFix.at(i))) {
			pileCalcul.push(tabPostFix.at(i));
		}
		else if (poidsOperateur(tabPostFix.at(i)) != -1)
		{
			valeur1 = stoi(pileCalcul.top());
			pileCalcul.pop();
			valeur2 = stoi(pileCalcul.top());
			pileCalcul.pop();
			string res = to_string(evaluerOperation(valeur2, valeur1, tabPostFix.at(i)[0]));
			pileCalcul.push(res);
		}

	}

	resultat = pileCalcul.top();
	return resultat;
}

void PostFix::evaluation() {
	string expression;
	cout << "Entrez l'expression a evaluer" << endl;
	cout << "\n**IMPORTANT**" << endl;
	cout << "(L'expression doit avoir des espaces entre chaques element" << endl;
	cout << "ex: ( 4 + 5 ) * 9" << endl;
	cout << "(4+5)*9 -----> ne fonctionnera pas)" << endl << endl;
	getline(cin, expression);

	transformerEnPostFix(expression);
	cout << "Expression transforme en postFix ---> " << postFix << endl;
	cout << "Resultat ---> " << evaluerExpressionPostFix() << endl;
}

void menu() {
	PostFix post;
	cout << "Bienvenue dans le calculateur d'expression!!!" << endl;
	post.evaluation();
}

int main() {
	menu();
	
	system("PAUSE");
	return 1;
}