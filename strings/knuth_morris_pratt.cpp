template<typename T> struct kmp {
    int P;
    vector<T> word;
    vi fail;

    int adv(int len, const T& nxt) const {
        while (len > 0 && word[len] != nxt)
            len = fail[len];
        return len + int(word[len] == nxt);
    }

    /*
     * Initializes the "failure table" for the search word.
     * For i > 0, fail[i] is the length of the longest proper
     * suffix of word[0, i) that is a prefix of word.
     */
    kmp(const vector<T>& word) : P(word.size()), word(word) {
        fail.resize(P + 1);
        for (int i = 2; i <= P; i++)
            fail[i] = adv(fail[i - 1], word[i - 1]);
    }

    /*
     * Finds all occurences of the search word in the given text.
     * match[i] indicates whether there exists a match starting at
     * index i of text.
     */
    vb find(const vector<T>& text) const {
        vb match(text.size());
        for (int i = 0, len = 0; i < text.size(); i++) {
            len = adv(len, text[i]);
            if (len == P) {
                match[i - len + 1] = true;
                len = fail[len];
            }
        }
        return match;
    }
};

