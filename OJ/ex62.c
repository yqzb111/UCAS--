#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie树节点结构
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;  // 标记是否为单词结尾
} TrieNode;

// 创建一个新的Trie树节点
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// 插入单词到Trie树中
void insert(TrieNode* root, const char* key) {
    TrieNode* pCrawl = root; // 从根节点开始遍历
    while (*key) {
        int index = *key - 'a'; // 计算字符在字母表中的索引
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode(); // 如果不存在对应字符的子节点，则创建一个新节点
        }
        pCrawl = pCrawl->children[index]; // 移动到子节点
        key++; // 移动到下一个字符
    }
    pCrawl->isEndOfWord = true; // 标记单词的结尾节点
}

// 查找单词是否在Trie树中
bool search(TrieNode* root, const char* key) {
    TrieNode* pCrawl = root; // 从根节点开始遍历
    while (*key) {
        int index = *key - 'a'; // 计算字符在字母表中的索引
        if (!pCrawl->children[index]) {
            return false; // 如果找不到对应字符的子节点，返回false
        }
        pCrawl = pCrawl->children[index]; // 移动到子节点
        key++; // 移动到下一个字符
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord); // 返回是否找到单词并且是单词的结尾
}

// 检查Trie树节点是否为空
bool isEmpty(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            return false;
        }
    }
    return true;
}

// 删除Trie树中的单词
bool delete(TrieNode* root, const char* key, int depth) {
    if (root == NULL) {
        return false; // 如果Trie树为空，返回false
    }
    if (*key) {
        int index = *key - 'a'; // 计算字符在字母表中的索引
        if (delete(root->children[index], key + 1, depth + 1)) {
            free(root->children[index]); // 递归删除子节点
            root->children[index] = NULL;
            return !root->isEndOfWord && isEmpty(root);
        }
    } else {
        if (root->isEndOfWord) {
            root->isEndOfWord = false; // 如果到达单词结尾，取消结尾标记
            return isEmpty(root);
        }
    }
    return false;
}

int main() {
    TrieNode* root = createNode();
    char operation[4];
    char word[100];
    char operations[1000][4];
    char words[1000][100];
    int count = 0;

    while (scanf("%s %s", operation, word) != EOF) {
        strcpy(operations[count], operation);
        strcpy(words[count], word);
        count++;
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(operations[i], "1") == 0) {
            insert(root, words[i]);
        } else if (strcmp(operations[i], "2") == 0) {
            delete(root, words[i], 0);
        } else if (strcmp(operations[i], "3") == 0) {
            if (search(root, words[i])) {
                printf("True\n");
            } else {
                printf("False\n");
            }
        }
    }

    return 0;
}
