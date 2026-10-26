# Priority Music Scheduler

## Overview

This project implements a priority-based music scheduling system
inspired by the TV program *Night Ahangi*. Music requests are processed
using queues and scheduled using a binary tree (priority queue) to
maximize user satisfaction within a one-hour broadcast window.

## Features

-   Object-oriented C++ implementation
-   Queue-based input and category management
-   Priority-based scheduling using binary trees
-   Detailed statistical output per music category

## Data Structures Used

-   Queue
-   Priority Queue (Binary Heap)
-   Classes and Objects

## Input Format

Each line of input follows the format:

    Category:Requests:Duration

Example:

    S:8:90
    P:6:120
    K:2:180
    M:5:300

## How to Build and Run

    g++ src/main.cpp src/Scheduler.cpp -o scheduler
    ./scheduler

## Output

The program prints: - Total playtime per category - Satisfaction level
per category - Percentage of broadcast time used

## Author

Sara Shekarchi Zade
