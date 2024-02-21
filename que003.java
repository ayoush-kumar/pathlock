import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.*;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

public class UserApiClient {

    // Data structure to store user information
    static class User {
        int age;
        String email;

        User(int age, String email) {
            this.age = age;
            this.email = email;
        }
    }

    // Function to make API request and return JSON response
    private static String makeApiRequest(String apiUrl) throws IOException {
        URL url = new URL(apiUrl);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();

        // Read response
        Scanner scanner = new Scanner(connection.getInputStream());
        StringBuilder response = new StringBuilder();
        while (scanner.hasNextLine()) {
            response.append(scanner.nextLine());
        }
        scanner.close();

        return response.toString();
    }

    // Function to fetch user data from API and store in a map
    private static Map<String, User> fetchAndStoreUserData(String apiUrl) {
        Map<String, User> userMap = new HashMap<>();

        try {
            String apiResponse = makeApiRequest(apiUrl);

            // Parse JSON response
            Gson gson = new Gson();
            JsonObject jsonData = gson.fromJson(apiResponse, JsonObject.class);

            // Store user information in the map
            JsonArray usersArray = jsonData.getAsJsonArray("users");
            for (JsonElement userElement : usersArray) {
                JsonObject userJson = userElement.getAsJsonObject();
                String username = userJson.get("username").getAsString();
                int age = userJson.get("age").getAsInt();
                String email = userJson.get("email").getAsString();

                userMap.put(username, new User(age, email));
            }
        } catch (IOException e) {
            System.err.println("Failed to fetch data from the API: " + e.getMessage());
        }

        return userMap;
    }

    // Function to sort user data alphabetically based on usernames
    private static Map<String, User> sortUserData(Map<String, User> userMap) {
        Map<String, User> sortedUserMap = new TreeMap<>(userMap);
        return sortedUserMap;
    }

    // Function to search for user details by username
    private static void searchUser(Map<String, User> userMap, String searchUsername) {
        User userDetails = userMap.get(searchUsername);
        if (userDetails != null) {
            System.out.println("User found - Username: " + searchUsername + ", Age: " + userDetails.age + ", Email: " + userDetails.email);
        } else {
            System.out.println("User not found.");
        }
    }

    public static void main(String[] args) {
        // API endpoint
        String apiUrl = "https://api.example.com/users";

        // Fetch and store user data
        Map<String, User> userMap = fetchAndStoreUserData(apiUrl);

        // Sort user data alphabetically based on usernames
        Map<String, User> sortedUserMap = sortUserData(userMap);

        // Display sorted user information
        System.out.println("Sorted User Information:");
        for (Map.Entry<String, User> entry : sortedUserMap.entrySet()) {
            String username = entry.getKey();
            User userDetails = entry.getValue();
            System.out.println("Username: " + username + ", Age: " + userDetails.age + ", Email: " + userDetails.email);
        }

        // Implement search functionality
        Scanner scanner = new Scanner(System.in);
        System.out.print("\nEnter username to search: ");
        String searchUsername = scanner.nextLine();
        searchUser(userMap, searchUsername);

        // Close the scanner
        scanner.close();
    }
}