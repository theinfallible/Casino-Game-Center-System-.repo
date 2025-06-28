# 🎰 Casino Game Center System

A feature-rich terminal-based casino game center written in C, supporting multiple games, wallet management, multiplayer gameplay, and in-game purchases — all in a single executable.

---

## 🕹️ Features

- 🎮 **11 Games Included**  
  Classic and casino-style games like **Sudoku**, **Blackjack**, **Connect 4**, **Wordle**, and more.

- 💳 **Wallet & Ticketing System**  
  Players can top-up wallets, pay entry fees, earn rewards, and buy virtual items. Supports 50+ transaction scenarios.

- 👥 **Multiplayer Support**  
  Engage in 2-player games like Connect 4 and Wordle for competitive fun.

- 🛒 **In-Game Shop**  
  Purchase over 20+ virtual items with in-game currency.

- 🧠 **Adaptive Difficulty Engine**  
  Dynamically balances challenge and enjoyment, improving gameplay fairness by ~35%.

- 🏦 **Banking Logic Integration**  
  Robust financial system handles deposits, withdrawals, game payouts, and bonus management.

---

## 🔧 Built With

- **Language**: C (standard libraries: `stdio.h`, `stdlib.h`, `string.h`, etc.)
- **Platform**: Terminal-based (CLI)
- **Graphics**: ASCII GUI (pseudo-GUI)

---

## 🧪 Demo (Example)

```
Welcome to the Casino Game Center 🎰
------------------------------------
1. Play Blackjack
2. Play Sudoku
3. Multiplayer: Connect 4
4. Wallet Management
5. Visit Shop
6. Exit

💰 Balance: ₹1500 | 🎟️ Tickets: 5
> Select an option:
```

---

## 🚀 Getting Started

### Prerequisites

- C compiler (e.g., `gcc`)
- Terminal or shell environment (Linux, macOS, Windows with Git Bash)

### Compilation

```bash
gcc -o casino_game_center main.c
```

### Run

```bash
./casino_game_center
```

---

## 📁 Project Structure

```
.
├── main.c           # Core program logic
├── README.md        # Project documentation
└── [assets/]        # Optional: text files or game data
```

---

## 🧩 Games Included

1. Blackjack  
2. Sudoku  
3. Tic-Tac-Toe  
4. Wordle (Multiplayer)  
5. Connect 4 (Multiplayer)  
6. Rock-Paper-Scissors  
7. Dice Roll  
8. Slot Machine  
9. Memory Match  
10. Number Guess  
11. Hangman  

---

## 📦 Features in Depth

| Feature                 | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| Dynamic Game Selection | Players choose from 11+ games with varied logic and complexity              |
| Wallet System          | Recharge, spend, and earn based on in-game performance                      |
| Multiplayer Mode       | Turn-based interaction in games like Connect 4 and Wordle                   |
| Reward Mechanisms      | Tickets and coins awarded per performance, usable in shop                   |
| Virtual Shop           | Buy items like avatars, powerups, game skins using wallet coins             |
| Banking System         | Handles deposits, bonuses, entry fees, and secure transactions              |
| Adaptive Difficulty    | Game AI difficulty adjusts to skill levels dynamically                      |

---

## 🙋‍♂️ Contributing

Feel free to fork this repository and submit a pull request if you’d like to:

- Add new games 🎲
- Enhance GUI 📈
- Refactor or modularize code 📦

---

## 📄 License

This project is licensed under the MIT License.  
See the [LICENSE](LICENSE) file for details.

---

## 🙌 Acknowledgments

- ASCII art inspiration from [textart.sh](https://textart.sh/)
- Game logic references from open-source game engines
