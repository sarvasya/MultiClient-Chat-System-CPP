# 💬 Multi-Client Chat System (C++)

A real-time multi-client chat application built using **C++ socket programming** and **multithreading**. This project demonstrates low-level TCP communication and concurrent client handling.

---

## 🚀 Features

* 🔗 TCP-based client-server communication
* 👥 Supports multiple clients simultaneously
* 🔄 Real-time message broadcasting
* 🧵 Multithreading for concurrent handling
* 🔒 Thread-safe client management using mutex
* ❌ Graceful client disconnection handling

---

## 🧠 Concepts Used

* Socket Programming (TCP/IP)
* Multithreading (`std::thread`)
* Synchronization (`std::mutex`)
* Client-Server Architecture
* Networking APIs (`socket`, `bind`, `listen`, `accept`, `connect`)

---

## 🛠️ Tech Stack

* Language: C++
* OS: Linux / macOS
* Libraries: POSIX Sockets, STL (thread, vector, mutex)

---

## 📦 How to Run

### 1️⃣ Compile

```bash
g++ server.cpp -o server -pthread
g++ client.cpp -o client -pthread
```

### 2️⃣ Run Server

```bash
./server
```

### 3️⃣ Run Clients (in different terminals)

```bash
./client
```

---

## 📸 Demo

Open multiple terminals and run clients to see real-time chat.

---

## 📌 Future Improvements

* Add usernames
* Private messaging
* GUI (Qt / Web frontend)
* Non-blocking I/O using epoll

---

## 🤝 Author

Built by Subhedu Sarkar
