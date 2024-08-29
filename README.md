<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->


<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="logo/Redfox_coding.jpg" alt="Logo" width="160" height="160">
  </a>

  <h3 align="center">PHILOSOPHERS</h3>



</div>


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

The Philosophers project, introduces US to multithreading and synchronization, 
focusing on concurrent programming concepts. The project is based on the "Dining Philosophers" problem, 
a classic example of a synchronization challenge involving processes (or threads) that share resources.

**Project Overview:**

You will simulate a group of philosophers sitting at a table, alternating between eating, thinking, and sleeping.
Each philosopher needs two forks to eat, but there is only one fork per philosopher, which leads to competition and potential deadlock.

**Key Objectives:**
- Multithreading: Use threads to simulate each philosopher’s actions concurrently.
- Synchronization: Manage shared resources (forks) using mutexes to prevent race conditions.
- Avoiding Deadlocks: Implement strategies to avoid deadlock situations where philosophers wait indefinitely for forks.
- Time Management: Ensure that philosophers act according to precise timing rules for eating, sleeping, and thinking.



<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

This is a C program so you need to have gcc compiler.
  ```sh
  sudo apt-get install gcc -y
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Lyyrst/Philosophers.git
2. Makefile !
   ```sh
   make && make clean
   ```
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

use this command :
```sh
./Philo [n_philosophers] [time to die] [time to eat] [time to sleep] [optional: n_meal]
```
Example:
```sh
./Philo 4 800 200 200
```
There is 4 philosophers, they die after 800 miliseconds without eating, and they take 200 milisecond to eat or sleep.
```sh
./Philo 4 800 200 200 5
```
The simulation stop when all philosopher get 5 meals.
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

[Discord : lyrst](https://discord.com/users/257192704537001984)

kurt.butorp@gmail.com

## Reminder

Please remember that this project is one of the first i did as a computer science learner, it does not reflect my actual skills but through which project i learned programming.
