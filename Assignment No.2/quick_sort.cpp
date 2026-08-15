#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Movie {
    string title;
    double rating;
    int release_year;
    int popularity;
};

// Swap two movies
void swapMovie(Movie& a, Movie& b) {
    Movie temp = a;
    a = b;
    b = temp;
}

// Partition function
int partition(vector<Movie>& movies, int low, int high, int choice) {

    Movie pivot = movies[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {

        bool condition = false;

        // Sort by Rating - highest first
        if (choice == 1) {
            condition = movies[j].rating > pivot.rating;
        }

        // Sort by Release Year - newest first
        else if (choice == 2) {
            condition = movies[j].release_year > pivot.release_year;
        }

        // Sort by Popularity - highest first
        else if (choice == 3) {
            condition = movies[j].popularity > pivot.popularity;
        }

        if (condition) {
            i++;
            swapMovie(movies[i], movies[j]);
        }
    }

    swapMovie(movies[i + 1], movies[high]);

    return i + 1;
}

// Quick Sort
void quickSort(vector<Movie>& movies, int low, int high, int choice) {

    if (low < high) {

        int pivot = partition(
            movies,
            low,
            high,
            choice
        );

        quickSort(
            movies,
            low,
            pivot - 1,
            choice
        );

        quickSort(
            movies,
            pivot + 1,
            high,
            choice
        );
    }
}

int main() {

    vector<Movie> movies;

    // Open dataset
    ifstream file("movies.csv");

    if (!file.is_open()) {
        cout << "File not found!" << endl;
        return 0;
    }

    string line;

    // Skip header
    getline(file, line);

    // Read dataset
    while (getline(file, line)) {

        stringstream ss(line);

        Movie movie;

        string rating;
        string release_year;
        string popularity;

        getline(ss, movie.title, ',');
        getline(ss, rating, ',');
        getline(ss, release_year, ',');
        getline(ss, popularity, ',');

        movie.rating = stod(rating);
        movie.release_year = stoi(release_year);
        movie.popularity = stoi(popularity);

        movies.push_back(movie);
    }

    file.close();

    cout << "Total Movies: " << movies.size() << endl;

    // User choice
    int choice;

    cout << "\nSort Movies By:\n";
    cout << "1. IMDb Rating\n";
    cout << "2. Release Year\n";
    cout << "3. Popularity\n";

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    // Apply Quick Sort
    if (!movies.empty()) {
        quickSort(
            movies,
            0,
            movies.size() - 1,
            choice
        );
    }

    // Display sorted movies
    cout << "\n\n";
    cout << "SORTED MOVIES\n";

    cout << "--------------------------------------------------------------------------------\n";

    cout << "Title                         Rating        Release Year        Popularity\n";

    cout << "--------------------------------------------------------------------------------\n";

    // Display first 10 movies
    int limit = movies.size();

    if (limit > 10)
        limit = 10;

    for (int i = 0; i < limit; i++) {

        cout << movies[i].title;

        // Spaces after title
        for (int j = movies[i].title.length(); j < 30; j++)
            cout << " ";

        cout << movies[i].rating;

        cout << "          ";

        cout << movies[i].release_year;

        cout << "                 ";

        cout << movies[i].popularity << endl;
    }

    cout << "--------------------------------------------------------------------------------\n";

    return 0;
}