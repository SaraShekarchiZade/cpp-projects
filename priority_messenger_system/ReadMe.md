# Priority Messenger System (پیام رسان اولویتی)

## Overview
This is a C++ program that simulates a messaging system where messages are sent based on priority. Higher priority messages are sent first. If multiple messages have the same priority, older messages are sent first.

**Message Priorities:**
- Text: 5
- Image: 4
- Audio: 3
- Video: 2

## Features
1. Priority-based message sending
2. Time-based simulation (500 bytes/sec sending speed)
3. Message file update after sending
4. Display statistics:
   - Total bytes sent per user pair
   - Total messages exchanged per user pair

## Input File Format
Each user has a file (e.g., `user1.txt`) containing messages in this format:

DesId|SourceId,MessageType,ContentId,VolumeByte,SendTime|ReceiveTime,Status

makefile
Copy code

**Example:**
2|1,Text,C001,450,1700000000|0,1

markdown
Copy code

## Usage
1. Compile the program:
g++ -std=c++11 -o priority_messenger main.cpp

markdown
Copy code
2. Run the program:
./priority_messenger

markdown
Copy code
3. Choose from the menu:
   - `1` → Send pending messages
   - `2` → Show statistics
   - `0` → Exit

## Notes
- `Status = 1` → unsent, `2` → sent, `3` → seen
- Sending speed is fixed at 500 bytes/sec
- Multiple message types can be queued and sent based on priority