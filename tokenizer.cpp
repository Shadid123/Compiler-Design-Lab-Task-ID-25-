#include <bits/stdc++.h>
using namespace std;

enum class TokenType {
    Identifier,
    Keyword,
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    Operator,
    Delimiter,
    Comment,
    EndOfFile,
    Unknown
};

struct Token {
    TokenType type;
    string lexeme;
    int line;
    int column;
};

static const unordered_set<string> keywords = {
    "int","float","double","char","void","if","else","for","while","do",
    "return","break","continue","const","struct","switch","case","default",
    "sizeof","typedef","static","extern","enum","union","goto","signed",
    "unsigned","long","short","auto","register"
};

class Lexer {
    string src;
    size_t i = 0;
    int line = 1;
    int col = 1;

public:
    Lexer(const string &s): src(s) {}

    vector<Token> tokenize() {
        vector<Token> tokens;
        while (true) {
            skipWhitespace();
            if (eof()) {
                tokens.push_back(makeToken(TokenType::EndOfFile, "", line, col));
                break;
            }
            char c = peek();
            if (isalpha(c) || c == '_') {
                tokens.push_back(lexIdentifierOrKeyword());
            } else if (isdigit(c) || (c == '.' && isdigit(peek(1)))) {
                tokens.push_back(lexNumber());
            } else if (c == '"' || c == '\'') {
                tokens.push_back(lexString());
            } else if (c == '/' && peek(1) == '/') {
                tokens.push_back(lexLineComment());
            } else if (c == '/' && peek(1) == '*') {
                tokens.push_back(lexBlockComment());
            } else {
                tokens.push_back(lexOperatorOrDelimiter());
            }
        }
        return tokens;
    }

private:
    bool eof() const { return i >= src.size(); }
    char peek(int ahead = 0) const { return eof() ? '\0' : src[i + ahead]; }
    char get() {
        if (eof()) return '\0';
        char c = src[i++];
        if (c == '\n') { line++; col = 1; }
        else col++;
        return c;
    }
    Token makeToken(TokenType t, const string &lex, int L, int C) {
        return Token{t, lex, L, C};
    }

    void skipWhitespace() {
        while (!eof() && isspace(peek())) get();
    }

    Token lexIdentifierOrKeyword() {
        int L = line, C = col;
        string s;
        while (!eof() && (isalnum(peek()) || peek() == '_')) s.push_back(get());
        if (keywords.count(s)) return makeToken(TokenType::Keyword, s, L, C);
        return makeToken(TokenType::Identifier, s, L, C);
    }

    Token lexNumber() {
        int L = line, C = col;
        string s;
        bool hasDot = false;
        // Leading dot handling: .5
        if (peek() == '.') {
            hasDot = true;
            s.push_back(get());
        }
        while (!eof() && (isdigit(peek()) || peek() == '.')) {
            if (peek() == '.') {
                if (hasDot) break; // second dot -> stop
                hasDot = true;
            }
            s.push_back(get());
        }
        if (!hasDot) return makeToken(TokenType::IntegerLiteral, s, L, C);
        else return makeToken(TokenType::FloatLiteral, s, L, C);
    }

    Token lexString() {
        int L = line, C = col;
        char quote = get(); // ' or "
        string s;
        s.push_back(quote);
        bool escaped = false;
        while (!eof()) {
            char c = get();
            s.push_back(c);
            if (escaped) {
                escaped = false;
            } else {
                if (c == '\\') escaped = true;
                else if (c == quote) break;
                else if (c == '\n') break; // unterminated string -> stop
            }
        }
        return makeToken(TokenType::StringLiteral, s, L, C);
    }

    Token lexLineComment() {
        int L = line, C = col;
        string s;
        s.push_back(get()); // '/'
        s.push_back(get()); // '/'
        while (!eof() && peek() != '\n') s.push_back(get());
        return makeToken(TokenType::Comment, s, L, C);
    }

    Token lexBlockComment() {
        int L = line, C = col;
        string s;
        s.push_back(get()); // '/'
        s.push_back(get()); // '*'
        while (!eof()) {
            char c = get();
            s.push_back(c);
            if (c == '*' && peek() == '/') {
                s.push_back(get()); // consume '/'
                break;
            }
        }
        return makeToken(TokenType::Comment, s, L, C);
    }

    Token lexOperatorOrDelimiter() {
        int L = line, C = col;
        char c = peek();
        // Multi-character operators to consider
        string two;
        two.push_back(peek());
        two.push_back(peek(1));
        static const unordered_set<string> twoCharOps = {
            "==","!=","<=",">=","++","--","&&","||","+=","-=","*=","/=","->","::"
        };
        if (!eof() && !eofAt(1) && twoCharOps.count(two)) {
            string s;
            s.push_back(get());
            s.push_back(get());
            return makeToken(TokenType::Operator, s, L, C);
        }

        // Single-char operators and delimiters
        string s;
        s.push_back(get());
        char ch = s[0];
        static const string ops = "+-*/%=<>&|^~!";
        static const string delims = "();{},[]:.?#";

        if (ops.find(ch) != string::npos) return makeToken(TokenType::Operator, s, L, C);
        if (delims.find(ch) != string::npos) return makeToken(TokenType::Delimiter, s, L, C);
        // Unknown
        return makeToken(TokenType::Unknown, s, L, C);
    }

    bool eofAt(int ahead) const {
        return (i + ahead) >= src.size();
    }
};

static string tokenTypeName(TokenType t) {
    switch (t) {
        case TokenType::Identifier: return "Identifier";
        case TokenType::Keyword: return "Keyword";
        case TokenType::IntegerLiteral: return "Integer";
        case TokenType::FloatLiteral: return "Float";
        case TokenType::StringLiteral: return "String";
        case TokenType::Operator: return "Operator";
        case TokenType::Delimiter: return "Delimiter";
        case TokenType::Comment: return "Comment";
        case TokenType::EndOfFile: return "EOF";
        default: return "Unknown";
    }
}

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    if (argc >= 2) {
        // Read file into string
        ifstream ifs(argv[1]);
        if (!ifs) {
            cerr << "Cannot open file: " << argv[1] << "\n";
            return 1;
        }
        stringstream ss;
        ss << ifs.rdbuf();
        input = ss.str();
    } else {
        // Read stdin
        stringstream ss;
        ss << cin.rdbuf();
        input = ss.str();
    }

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    // Print tokens
    for (const auto &t : tokens) {
        if (t.type == TokenType::EndOfFile) {
            cout << "[EOF] at " << t.line << ":" << t.column << "\n";
            continue;
        }
        cout << tokenTypeName(t.type)
             << " \"" << t.lexeme << "\""
             << "  at " << t.line << ":" << t.column << "\n";
    }

    return 0;
}
