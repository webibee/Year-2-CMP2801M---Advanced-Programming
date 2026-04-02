# LincBank – C++ Banking Application
Course: CMP2801M – Advanced Programming
Institution: University of Lincoln
Grade Received: 80%
Language: C++17
Tools: Visual Studio 2019, Git

# Overview
LincBank is a command-line banking simulation written in modern C++. It allows users to create multiple account types (Current, Savings, ISA), perform deposits/withdrawals/transfers, and project compound interest on savings accounts. The project demonstrates advanced C++ techniques, including abstract base classes, polymorphism, manual memory management, and STL containers.

The application does not persist data – all accounts and transactions exist only during program execution, as required by the brief.

# Features
- Open account	Current (1 max, £500 overdraft), Savings (0.85% interest), ISA (1.15% interest, £1000 minimum deposit)
- View account(s): Single account by index, or all accounts with transaction history
- Deposit / Withdraw	input validation and overdraft protection
- Transfer	between any two accounts with automatic timestamp consistency
- Project interest: Compute compound interest for savings accounts (n=12 compounding periods/year)
- Transaction history: Each account stores timestamps, amounts, and transaction types

# Technologies Used
Language: C++17
STL Components: vector, string, ctime, cmath
OOP Paradigms: Abstract classes, pure virtual functions, multiple inheritance (interface)
Memory Management: Raw pointers, dynamic allocation with new, manual delete in destructor
Build System: Visual Studio Solution (.sln)

# Class Architecture
Account (abstract)
├── Current
└── Savings ── implements ── InterestEarning (interface)

Transaction (helper class)

- Account defines pure virtual methods: deposit(), withdraw(), getBalance(), getHistory(), etc.
- Current adds a £500 overdraft limit.
- Savings implements computeInterest() using the compound interest formula.
- InterestEarning is a pure virtual interface – demonstrates interface segregation.
- Transaction stores description, value, timestamp, and direction (incoming/outgoing).
