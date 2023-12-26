#include "ready_set_bool.hpp"
#include "Proposition.hpp"

namespace m42 {

    const std::string Proposition::TreeNode::valid_tokens = "01ABCDEFGHIJKLMNOPQRSTUVWXYZ!&|^>=";

    Proposition::TreeNode::TreeNode(char token, TreeNode *left, TreeNode *right)
    : token(token), left(left), right(right) {
        if (valid_tokens.find(token) == std::string::npos)
            throw std::invalid_argument("Invalid token");
    }

    Proposition::TreeNode::TreeNode(char token) : TreeNode(token, nullptr, nullptr) {}

    Proposition::TreeNode::~TreeNode() {
        delete left;
        delete right;
    }

    Proposition::Proposition() : _root(nullptr) {}

    Proposition::Proposition(const std::string &formula) : Proposition() {
        _parse_formula(formula);
    }

    Proposition::Proposition(const Proposition &other) : _root(_copy_tree(other._root)), _vars(other._vars) {}

    Proposition::Proposition(Proposition &&other) noexcept : _root(other._root), _vars(std::move(other._vars)) {
        other._root = nullptr;
    }

    Proposition &Proposition::operator=(Proposition other) {
        std::swap(_root, other._root);
        std::swap(_vars, other._vars);
        return *this;
    }

    Proposition::~Proposition() {
        delete _root;
    }

    [[maybe_unused]] void Proposition::print_tree() const {
        _print_node(_root, 0);
    }

    const std::map<char, size_t> &Proposition::vars() const {
        return _vars;
    }

    std::string Proposition::postfix_notation() const {
        return _postfix_notation(_root);
    }

    bool Proposition::evaluate() const {
        return _evaluate_node(_root);
    }

    void Proposition::substitute_values(const std::map<char, bool> &values) {
        _substitute_values(_root, values);
    }

    void Proposition::to_negation_normal_form() {

    }

    void Proposition::_parse_formula(const std::string &formula) {
        std::stack<TreeNode *> stack;

        for (char c : formula) {
            c = static_cast<char>(std::toupper(c));

            if (Proposition::TreeNode::valid_tokens.find(c) == std::string::npos)
                throw std::invalid_argument("Formula contains invalid tokens");

            auto *node = new TreeNode(c);

            if (std::isalnum(c)) {
                stack.push(node);
                if (std::isalpha(c)) _vars[c]++;
                continue;
            }

            switch (c) {
                case '!':
                    if (stack.empty())
                        throw std::invalid_argument("Invalid formula");
                    node->left = stack.top();
                    stack.pop();
                    stack.push(node);
                    break;
                case '&':
                case '|':
                case '^':
                case '>':
                case '=':
                    if (stack.size() < 2)
                        throw std::invalid_argument("Invalid formula");
                    pop_two(stack, node->left, node->right);
                    stack.push(node);
                    break;
                default:
                    break;
            }
        }

        if (stack.size() != 1)
            throw std::invalid_argument("Invalid formula");

        _root = stack.top();
    }

    Proposition::TreeNode *Proposition::_copy_tree(TreeNode *node) {
        if (node == nullptr)
            return nullptr;
        return new TreeNode(
            node->token,
            _copy_tree(node->left),
            _copy_tree(node->right)
        );
    }

    std::string Proposition::_postfix_notation(TreeNode *node) {
        std::string result;
        if (node->left)
            result += _postfix_notation(node->left);
        if (node->right)
            result += _postfix_notation(node->right);
        result += node->token;
        return result;
    }

    void Proposition::_print_node(TreeNode *node, int space) {
        if (node == nullptr)
            return;
        space += 2;
        _print_node(node->right, space);
        for (int i = 2; i < space; ++i)
            std::cout << ' ';
        std::cout << node->token << std::endl;
        _print_node(node->left, space);
    }

    bool Proposition::_evaluate_node(TreeNode *node) {
        if (std::isalpha(node->token))
            throw std::runtime_error("Can not evaluate proposition with variables");
        if (node->token == '0' || node->token == '1')
            return node->token == '1';

        switch (node->token) {
            case '!':
                return !_evaluate_node(node->left);
            case '&':
                return _evaluate_node(node->left) && _evaluate_node(node->right);
            case '|':
                return _evaluate_node(node->left) || _evaluate_node(node->right);
            case '^':
                return _evaluate_node(node->left) != _evaluate_node(node->right);
            case '>':
                return !_evaluate_node(node->left) || _evaluate_node(node->right);
            case '=':
                return _evaluate_node(node->left) == _evaluate_node(node->right);
            default:
                throw std::runtime_error("Invalid token");
        }
    }

    void Proposition::_substitute_values(TreeNode *node, const std::map<char, bool> &values) {
        if (node->left)
            _substitute_values(node->left, values);
        if (node->right)
            _substitute_values(node->right, values);
        if (std::isalpha(node->token))
            try {
                _vars[node->token]--;
                if (_vars[node->token] == 0)
                    _vars.erase(node->token);
                node->token = values.at(node->token) ? '1' : '0';
            } catch (std::out_of_range &e) {
                throw std::invalid_argument("Values map does not contain all variables");
            }
    }

}
