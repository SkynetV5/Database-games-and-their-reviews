#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
class Game{
private:
    string title;
    string developer;
    string review;
public:
    void print_cvs(){
        cout << "\"";
        for(int i = 0; i < (int)title.length(); i++){
                    if(title[i] == '_') {
                        cout << " ";
                    }
                    else {
                        cout << title[i];
                    }
                }
        cout << "\";\"";
        for(int i = 0; i < (int)developer.length(); i++){
                    if(developer[i] == '_') {
                        cout << " ";
                    }
                    else {
                        cout << developer[i];
                    }
                }
        cout << "\";";
        if(review != "brak"){
                cout << "\"";
                for(int i = 0; i < (int)review.length(); i++){
                    if(review[i] == '_') {
                        cout << " ";
                    }
                    else {
                        cout << review[i];
                    }
                }
                cout << "\"";
        }
    }

    void print_list(){
        cout << "\"";
        for(int i = 0; i < (int)title.length(); i++){
                    if(title[i] == '_') {
                        cout << " ";
                    }
                    else {
                        cout << title[i];
                    }
                }
        cout << "\" \"";
        for(int i = 0; i < (int)developer.length(); i++){
                    if(developer[i] == '_') {
                        cout << " ";
                    }
                    else {
                        cout << developer[i];
                    }
                }
        cout << "\"";
        if(review != "brak"){
                cout << " \"";
                for(int i = 0; i < (int)review.length(); i++){
                    if(review[i] == '_') {
                        cout << " ";
                    }
                    else {
                        cout << review[i];
                    }
                }
                cout << "\"";
        }
    }
    
    void add(string title,string developer){
        title[0] = toupper(title[0]);
        for(int i = 1; i < (int)title.length(); i++){
            if(title[i] == ' '){
                title[i] = '_';
            }
        }
        Game::title = title;
        developer[0] = toupper(developer[0]);
        for(int i = 1; i < (int)developer.length(); i++){
            if(developer[i] == ' '){
                developer[i] = '_';
            }
        }
        Game::developer = developer;
        Game::review = "brak";
    }
    void set(string title,string developer,string review){
        Game::title = title;
        Game::developer = developer;
        Game::review = review;
    }

    void add_review(string review){
        for(int i = 0; i < (int)review.length(); i++){
            if(review[i] == ' '){
                review[i] = '_';
            }
        }
        Game::review = review;
    }
    string print_title() {return title;}
    string print_developer() {return developer;}
    string print_review() {return review;}

    bool static sort_by_title(const Game& game1, const Game& game2){
        return game1.title < game2.title;
    }

    bool static sort_by_developer(const Game& game1, const Game& game2){
        return game1.developer < game2.developer;
    }
    bool static sort_by_review(const Game& game1, const Game& game2){
        return game1.review < game2.review;
    }

    bool static search_by_frase(string frase, string title,string developer,string review){
        for(int i = 0; i < (int)frase.length(); i++){
            if(frase[i] == ' '){
                frase[i] = '_';
            }
            else{
               frase[i] = tolower(frase[i]);
            }
        }
        for(int i = 0; i < (int)title.length(); i++){
                title[i] = tolower(title[i]);
        }
        for(int i = 0; i < (int)developer.length(); i++){
                developer[i] = tolower(developer[i]);
        }
        for(int i = 0; i < (int)review.length(); i++){
                review[i] = tolower(review[i]);
        }
        size_t search_title = title.find(frase);
        size_t search_developer = developer.find(frase);
        size_t search_review = review.find(frase);
        if(search_title != string::npos || search_developer != string::npos || search_review != string::npos){
            return true;
        }
        return false;
    }
};


Game game;
string title = "";
string developer = "";
string review = "";

void save_file(vector<Game>games, fstream& file){
    int size = games.size();
    for(int i = 0; i < size; i++){
        file << games[i].print_title() << " ";
        file << games[i].print_developer() << " ";
        file << games[i].print_review() << endl;
    }
    file.close();
}

void check_id(char *argument,vector<Game>games, fstream& file){
    for(int i = 0; i < (int)strlen(argument); i++){
        if(isdigit(argument[i]) == 0){
            save_file(games,file);
            throw invalid_argument("ID nie jest liczba!");
        }
    }
}
void check_col_number(char *argument,vector<Game>games, fstream& file){
    for(int i = 0; i < (int)strlen(argument); i++){
        if(isdigit(argument[i]) == 0){
            save_file(games,file);
            throw invalid_argument("Podany numer nie jest liczba!");
        }
    }
}

void command_add(int argc,char *argv[],vector<Game>&games, fstream& file){
    if(argc < 4){
            save_file(games,file);
            throw invalid_argument("Uzycie funkcji: add \'tytul\' \'deweloper\'");
        }
        else{
            title = argv[2];
            developer = argv[3];
            game.add(title,developer);
            games.push_back(game);
            cout << "Numer ID dodanej gry do bazy: " << games.size() << endl;
        }
}

void command_review(int argc,char *argv[],vector<Game>&games, fstream& file,int size){
    if(argc < 4){
            save_file(games,file);
            throw invalid_argument("Uzycie funkcji: review [ID] \'tresc recenzji\'");
        }
        review = argv[3];
        check_id(argv[2],games,file);
        int id = atoi(argv[2]);
        size = games.size();
        if(id > size || id < 0){
            save_file(games,file);
            throw invalid_argument("Nie ma takiej gry o takim ID");
        }
        games[id - 1].add_review(review);
        cout << "Recenzja dla gry od ID " << id << " zostala dodana" << endl;
}

void command_search(int argc,char *argv[],vector<Game>&games, fstream& file,int size){
    if(argc < 4){
            save_file(games,file);
            throw invalid_argument("Uzycie funkcji: search \'fraza\' [numer kolumny do sortowania]");
        }
        check_col_number(argv[3],games,file);
        int col_number = atoi(argv[3]);
        vector<Game> search_games;
        size = games.size();
        string frase = argv[2];
        cout << "Lista gier: " <<endl;
        cout << "ID " << "Tytul " << "Deweloper " << "Recenzja(jesli istnieje) " << endl; 
        for(int i = 0; i < (int)games.size(); i++){
            title = games[i].print_title();
            developer = games[i].print_developer();
            review = games[i].print_review();
            if(games[i].search_by_frase(frase,title,developer,review)){
                search_games.push_back(games[i]);
            }
        }
        size = search_games.size();
            if(col_number == 1){
                for(int i = 0 ; i < size; i++){
                cout << (i + 1) << " ";
                search_games[i].print_list();
                cout << endl;
                }
            }
            if(col_number == 2){
                sort(search_games.begin(),search_games.end(),Game::sort_by_title);
                for(int i = 0 ; i < size; i++){
                    cout << (i + 1) << " ";
                    search_games[i].print_list();
                    cout << endl;
                }
            }
            if(col_number == 3){
                sort(search_games.begin(),search_games.end(),Game::sort_by_developer);
                for(int i = 0 ; i < size; i++){
                    cout << (i + 1) << " ";
                    search_games[i].print_list();
                    cout << endl;
                }
            }
            if(col_number == 4){
                sort(search_games.begin(),search_games.end(),Game::sort_by_review);
                for(int i = 0 ; i < size; i++){
                    cout << (i + 1) << " ";
                    search_games[i].print_list();
                    cout << endl;
                }
            }
}

void command_list(int argc,char *argv[],vector<Game>&games, fstream& file,int size){
    if(argc == 4){
            save_file(games,file);
            throw invalid_argument("Uzycie funkcji: list [numer kolumny]");
        }
        if(argc == 3){
            check_col_number(argv[2],games,file);
            int col_number = atoi(argv[2]);
            vector<Game> sortedgames;
            sortedgames = games;
            size = sortedgames.size();
            cout << "Lista gier: " <<endl;
            cout << "ID " << "Tytul " << "Deweloper " << "Recenzja(jesli istnieje) " << endl; 
            if(col_number == 1){
                for(int i = 0 ; i < size; i++){
                cout << (i + 1) << " ";
                sortedgames[i].print_list();
                cout << endl;
                }
            }
            if(col_number == 2){
                sort(sortedgames.begin(),sortedgames.end(),Game::sort_by_title);
                for(int i = 0 ; i < size; i++){
                    cout << (i + 1) << " ";
                    sortedgames[i].print_list();
                    cout << endl;
                }
            }
            if(col_number == 3){
                sort(sortedgames.begin(),sortedgames.end(),Game::sort_by_developer);
                for(int i = 0 ; i < size; i++){
                    cout << (i + 1) << " ";
                    sortedgames[i].print_list();
                    cout << endl;
                }
            }
            if(col_number == 4){
                sort(sortedgames.begin(),sortedgames.end(),Game::sort_by_review);
                for(int i = 0 ; i < size; i++){
                    cout << (i + 1) << " ";
                    sortedgames[i].print_list();
                    cout << endl;
                }
            }
        }
        else{
            size = games.size();
            cout << "Lista gier: " <<endl;
            cout << "ID " << "Tytul " << "Deweloper " << "Recenzja(jesli istnieje) " << endl; 
            for(int i = 0 ; i < size; i++){
                cout << (i + 1) << " ";
                games[i].print_list();
                cout << endl;
            }
        }
}

void command_delete(int argc,char *argv[],vector<Game>&games, fstream& file,int size){
    if(argc < 3){
            save_file(games,file);
            throw invalid_argument("Uzycie funkcji: delete [ID]");
        }
        check_id(argv[2],games,file);
        int id = atoi(argv[2]);
        size = games.size();
        if(id < 0 || id > size){
            save_file(games,file);
            throw invalid_argument("Nie ma takiej gry o takim ID");
        }
        games.erase(games.begin()+ (id -1));
        cout << "Gra o ID " << id << " zostal usuniety" << endl;
}
void command_csv(int argc,vector<Game>&games,fstream& file,int size){
    if(argc > 2){
            save_file(games,file);
            throw invalid_argument("Uzycie funkcji: csv ");
        }
    size = games.size();
        cout << "Lista gier: " <<endl;
        cout << "ID " << "Tytul " << "Deweloper " << "Recenzja(jesli istnieje) " << endl; 
        for(int i = 0 ; i < size; i++){
            cout << (i + 1) << ";";
            games[i].print_cvs();
            
            cout << endl;
        }
}
void commands_list(int argc,char *argv[], vector<Game>&games,fstream& file){
    string command = argv[1];
    int size;
     if(command == "add"){
        command_add(argc,argv,games,file);
    }
    else if(command == "review"){
        command_review(argc,argv,games,file,size);
    }
    else if(command == "search"){
        command_search(argc,argv,games,file,size);
    }
    else if(command == "list"){
        command_list(argc,argv,games,file,size);
       
    }
    else if(command == "delete"){
        command_delete(argc,argv,games,file,size);
    }
    else if(command == "csv"){
        command_csv(argc,games,file,size);   
    }
    else{
        save_file(games,file);
        throw invalid_argument("Nieznana komenda.");
    }
}

void insert_games_to_vector(vector<Game>&games,fstream& file){
    file.open("database_games.txt", ios::in);
        while(!file.eof()){
            file >> title;
            file >> developer;
            file >> review;
            game.set(title,developer,review);
            if(title != "" && developer != "" && review != ""){
            games.push_back(game);
            }
            title = "";
            developer = "";
            review = "";

        }
    file.close();
}

int main(int argc, char *argv[]){
    try{
        bool isEmpty = 1;
        fstream file;
        vector<Game> games;
        
    if(argc < 2 || argc > 4){
        string wrong_argument = "Uzycie : ./games.exe <opcje>";
        throw invalid_argument(wrong_argument);
    }
    file.open("database_games.txt" , ios::in);
    if(!file.is_open()){
        cout << ("Brak pliku, tworze...\n");
        file.open("database_games.txt", ios::out);
        file.close();
        cout << ("Plik zostal utworzony.\n");
    }
    while(!file.eof()){
        string test;
        file >> test;
        if(test == "") isEmpty = 0;
        break;
    }
    file.close();
    if(isEmpty){
        insert_games_to_vector(games,file);
    }

    file.open("database_games.txt", ios::out);

    commands_list(argc,argv,games,file);

    save_file(games,file);
    
    }
    catch(const exception& e){
        cerr << e.what() << '\n';
    }
    return 0;
}