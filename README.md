---

### Detailed Description
<h3 align="center">This is a C++ program that finds and displays connections between the users. The data.csv file contains the list of names of people and the name of their friends. Connections Analyzer is a robust program developed to manage and analyze social network data from CSV files. It reads user connection data from `data/data.csv` and profession data from `data/stat.csv`. The program provides a suite of functionalities, including:

- **String Manipulation**: Convert strings to lowercase and split them by delimiters for easier handling and comparison.
- **Data Retrieval**: Extract user connections and professions from CSV files.
- **Data Display**: Display lists of users based on professions, skills, and connections.
- **User Interaction**: Prompt users for input and provide meaningful feedback based on the data.
- **Search Capabilities**: Search for user connections and display paths between users.

This tool is particularly useful for analyzing and visualizing social networks, providing insights into user professions and connections. By leveraging the various functions, users can easily explore and understand the relationships within a dataset.
</h3>

---

# The Real Linked Project

A command-line program that helps users explore connections, professions, and skills in a social network dataset. Users can search friends, view others in their profession, and more.

## Social Network Profiler

### Table of Contents
1. [Project Overview](#project-overview)
2. [Installation](#installation)
3. [How to Run](#how-to-run)
4. [Contributors](#contributors)
5. [License](#license)

---

### Project Overview
**Social Network Profiler** is a console-based application that allows users to search and navigate a social network database. The tool helps users discover people with similar professions, find individuals by specific skills, and navigate connections between people.

The application uses CSV files (`data.csv` and `stat.csv`) as the source of social network information, where:
- `data.csv` holds connection and profession data.
- `stat.csv` stores additional data like emails and detailed professional information.

Features include:
- Username validation and profile search.
- Professional group and skill-based searches.
- Pathfinding for connection navigation between users.

### Installation

1. **Prerequisites**: Ensure you have a C++ compiler (such as g++) installed.
2. **Download the Files**: Clone or download the repository containing:
   - `main.cpp`, `log.cpp`, `log.h`
   - CSV files: `data.csv` and `stat.csv`
3. **Compile the Program**:
   ```bash
   g++ main.cpp log.cpp -o SocialNetworkProfiler

### How to Run
Run the compiled program with:
```bash
./SocialNetworkProfiler
```

### Contributors
The contributors of this project are: [Samraat Jain](https://github.com/SamraatJain9)

### License
License
This project is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for details.
