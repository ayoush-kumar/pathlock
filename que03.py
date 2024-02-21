import requests
import json
import os

class UserAPI:
    def __init__(self):
        # Initialize the UserAPI class with the API URL, cache file, and an empty list for users
        self.url = "https://jsonplaceholder.typicode.com/users"
        self.cache_file = "user_cache.json"
        self.users = []

    def fetch_data(self):
        # Fetch user data either from the cache file or the API, and store it in the 'users' list
        if os.path.exists(self.cache_file):
            # If the cache file exists, load data from it
            with open(self.cache_file, 'r') as file:
                self.users = json.load(file)
        else:
            # If the cache file doesn't exist, make an API request to fetch data
            response = requests.get(self.url)
            if response.status_code == 200:
                self.users = response.json()
                # Cache the fetched data by writing it to the cache file
                with open(self.cache_file, 'w') as file:
                    json.dump(self.users, file)

    def sort_users(self):
        # Sort the users list alphabetically based on usernames
        self.users.sort(key=lambda user: user['username'])

    def search_user(self, username):
        # Search for a user in the 'users' list based on the provided username
        for user in self.users:
            if user['username'] == username:
                return user
        return None

if __name__ == "__main__":
    # Create an instance of the UserAPI class
    api = UserAPI()
    
    # Fetch user data and sort the users
    api.fetch_data()
    api.sort_users()

    # Main loop to search for users
    while True:
        search_username = input("Enter username to search (q to quit): ")
        if search_username.lower() == 'q':
            break
        user = api.search_user(search_username)
        if user:
            # Print user details if found
            print(f"User found: {user['name']}, {user['email']}, Age: {user['address']['zipcode']}")
        else:
            print("User not found.")
