#include <cctype>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//Kiranjot K. Bhatia, CS162, Program 3
//The purpose of this program is to allow the user to enter in a max of 10 social media posts
//and the information per post; including author's name, title, website/video, text, #of likes
//and any extra symbols(!)

//constants
const int POSTS = 10;			//Number of posts(MAX 10)
const int TITLE = 100;			//Title of post
const int AUTHOR = 100;			//Author of post				
const int TEXT = 100;			//Text of post
//const int WEBSITE_VIDEO = 100; 			//Website or video link
//const int SYMBOLS = 100; 		//Does text include any "!" symbol?

//Structure
struct post
{
	char title[TITLE];
	char author[AUTHOR];
	char text[TEXT];
	//char website_video[WEBSITE_VIDEO];
	int likes = 0;
	int count = 0;
};


//Prototypes

void read_posts(post library[], int& number_of_posts);
void display_posts(post librabry[], int number_of_posts);
void read_a_post(post& a_post);
void display_a_post(post& a_post);

int load(post library[]);    			//Returns the number of posts read in
void save(post library[], int number_to_save);



int main()
{
	post library[POSTS];
	int number_of_posts = 0;

	read_posts(library, number_of_posts);
	cout << "\nNumber of posts: " << number_of_posts << endl;

	display_posts(library, number_of_posts);

	//read_a_post(library[number_of_posts]);
	save(library, number_of_posts);

	return 0;
}



//Save the posts read to an external file

void save(post library[], int number_to_save)
{
	ofstream file_out;
	//	file_out.open("social.txt", ios::app);
	file_out.open("social.txt");
	if (file_out)
	{
		for (int i = 0; i < number_to_save; ++i)
		{
			file_out << library[i].title << '|'
				<< library[i].author << '|'
				<< library[i].text << '|'
				// << library[i].website_video << '|'
				<< library[i].likes << '|' << endl;
		}
		file_out.close();
	}
}

//Read information from the file

int load(post library[]) 		//Returns the number of posts read in
{
	ifstream file_in;
	int i = 0;

	//Load any posts stored in external file named as "social.txt"
	file_in.open("social.txt");
	if (file_in)
	{
		file_in.get(library[0].title, TITLE, '|');
		file_in.ignore(100, '|');

		while (!file_in.eof() && i < POSTS)
		{
			file_in.get(library[i].author, AUTHOR, '|');
			file_in.ignore(100, '|');
			file_in.get(library[i].text, TEXT, '|');
			file_in.ignore(100, '|');
			//	file_in.get(library[i].website_video, WEBSITE_VIDEO, '|');
				//file_in.ignore(100, '|');
			file_in >> library[i].likes;
			file_in.ignore(100, '|');
			++i;
			file_in.get(library[i].title, TITLE, '|');
			file_in.ignore(100, '|');
		}
		file_in.close();
	}
	return i;
}


void read_posts(post library[], int& number_of_posts)
{
	int i = number_of_posts;
	char response = 'n';
	cout << "Welcome to the post tracker program! This program will allow you to keep a track of the number of posts you put in and it's specific information." << endl;
	cout << "\nWould you like to enter in a new post(y/n)?";

	cin >> response;
	cin.ignore(100, '\n');

	while ('Y' == toupper(response) && i < POSTS)
	{
		read_a_post(library[i]);
		cout << "Would you like to enter in another post?(y/n): ";
		cin >> response;
		cin.ignore(100, '\n');
		++i;
	}

	number_of_posts = i;
}


void display_posts(post library[], int number_of_posts)
{
	for (int i = 0; i < number_of_posts; ++i)
	{
		display_a_post(library[i]);
	}
}

void read_a_post(post& a_post)
{

	cout << "\nPlease enter in the title of the post: ";
	cin.get(a_post.title, TITLE, '\n');
	cin.ignore(100, '\n');

	cout << "Author's name: ";
	cin.get(a_post.author, AUTHOR, '\n');
	cin.ignore(100, '\n');

	cout << "Enter text to display: ";
	cin.get(a_post.text, TEXT, '\n');
	cin.ignore(100, '\n');

	cout << "Number of likes: ";
	cin >> a_post.likes;

	while (a_post.likes < 0 || cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Enter a valid number of likes: ";
		cin >> a_post.likes;
	}
}


void display_a_post(post& one_post)
{
	cout << "\n" "Title: " << one_post.title << endl
		<< "Author: " << one_post.author << endl
		<< "Text: " << one_post.text << endl
		<< "Likes: " << one_post.likes << endl;
}
