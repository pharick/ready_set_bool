#include "ready_set_bool.hpp"
#include "Proposition.hpp"

namespace m42 {

    const std::string Proposition::TreeNode::valid_tokens = "01ABCDEFGHIJKLMNOPQRSTUVWXYZ!&|^>=";

    Proposition::TreeNode::TreeNode(char token, TreeNode *left, TreeNode *right)
    : token(token), left(left), right(right) {
        if (valid_tokens.find(token) == std::string::npos)
            throw std::invalid_argument("Invalid token");
        if (std::isalnum(token) && (left != nullptr || right != nullptr))
            throw std::invalid_argument("Leaf node can not have children");
        if (token == '!' && (left == nullptr || right != nullptr))
            throw std::invalid_argument("Unary operator must have one child");
        if (!std::isalnum(token) && token != '!' && (left == nullptr || right == nullptr))
            throw std::invalid_argument("Binary operator must have two children");
    }

    Proposition::TreeNode::TreeNode(char token, TreeNode *left) : TreeNode(token, left, nullptr) {}

    Proposition::TreeNode::TreeNode(char token) : TreeNode(token, nullptr, nullptr) {}

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
        _delete_tree(_root);
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

    bool Proposition::is_satisfiable() const {
        uint32_t max_values = extend_bit(true, vars().size());
        for (uint32_t values = 0; values <= max_values; ++values) {
            std::map<char, bool> v;
            size_t i = 0;
            for (auto c : vars()) {
                v[c.first] = (values >> (vars().size() - 1 - i++)) & 1;
            }
            Proposition p(*this);
            p.substitute_values(v);
            if (p.evaluate())
                return true;
        }
        return false;
    }

    void Proposition::substitute_values(const std::map<char, bool> &values) {
        _substitute_values(_root, values);
    }

    void Proposition::to_negation_normal_form() {
        _root = _to_negation_normal_form(_root);
    }

    void Proposition::to_conjunctive_normal_form() {
        to_negation_normal_form();
        _root = _negation_normal_form_to_conjunctive_normal_form(_root);
    }

    void Proposition::_parse_formula(const std::string &formula) {
        std::stack<TreeNode *> stack;

        for (char c : formula) {
            c = static_cast<char>(std::toupper(c));
            if (Proposition::TreeNode::valid_tokens.find(c) == std::string::npos)
            {
                _delete_stack(stack);
                throw std::invalid_argument("Formula contains invalid tokens");
            }

            if (std::isalnum(c)) {
                stack.push(new TreeNode(c));
                if (std::isalpha(c)) _vars[c]++;
                continue;
            }

            TreeNode *left, *right;
            switch (c) {
                case '!':
                    if (stack.empty()) {
                        _delete_stack(stack);
                        throw std::invalid_argument("Invalid formula");
                    }
                    left = stack.top();
                    stack.pop();
                    stack.push(new TreeNode(c, left));
                    break;
                case '&':
                case '|':
                case '^':
                case '>':
                case '=':
                    if (stack.size() < 2) {
                        _delete_stack(stack);
                        throw std::invalid_argument("Invalid formula");
                    }
                    pop_two(stack, left, right);
                    stack.push(new TreeNode(c, left, right));
                    break;
                default:
                    break;
            }
        }

        if (stack.size() != 1) {
            _delete_stack(stack);
            throw std::invalid_argument("Invalid formula");
        }

        _root = stack.top();
    }

    void Proposition::_delete_tree(TreeNode *node) {
        if (node == nullptr)
            return;
        _delete_tree(node->left);
        _delete_tree(node->right);
        delete node;
    }

    void Proposition::_delete_stack(std::stack<TreeNode *> &stack) {
        while (!stack.empty()) {
            _delete_tree(stack.top());
            stack.pop();
        }
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

    Proposition::TreeNode *Proposition::_to_negation_normal_form(TreeNode *node) {
        if (node == nullptr)
            return nullptr;

        if (node->left)
            node->left = _to_negation_normal_form(node->left);
        if (node->right)
            node->right = _to_negation_normal_form(node->right);

        TreeNode *new_node;
        switch (node->token) {
            case '=':
                new_node = new TreeNode(
                    '|',
                    new TreeNode('&', _copy_tree(node->left), _copy_tree(node->right)),
                    new TreeNode(
                        '&',
                        new TreeNode('!', _copy_tree(node->left)),
                        new TreeNode('!', _copy_tree(node->right))
                    )
                );
                _delete_tree(node);
                return _to_negation_normal_form(new_node);
            case '>':
                new_node = new TreeNode(
                    '|',
                    new TreeNode('!', node->left),
                    node->right
                );
                delete node;
                return _to_negation_normal_form(new_node);
            case '^':
                new_node = new TreeNode(
                    '|',
                    new TreeNode(
                        '&',
                        new TreeNode('!',_copy_tree(node->left)),
                        _copy_tree(node->right)
                    ),
                    new TreeNode(
                        '&',
                        _copy_tree(node->left),
                        new TreeNode('!',_copy_tree(node->right))
                    )
                );
                _delete_tree(node);
                return _to_negation_normal_form(new_node);
            case '!':
                if (node->left->token == '!') {
                    new_node = node->left->left;
                    delete node->left;
                    delete node;
                    return _to_negation_normal_form(new_node);
                }
                if (node->left->token == '&' || node->left->token == '|') {
                    new_node = new TreeNode(
                        node->left->token == '&' ? '|' : '&',
                        new TreeNode('!', node->left->left),
                        new TreeNode('!', node->left->right)
                    );
                    delete node->left;
                    delete node;
                    return _to_negation_normal_form(new_node);
                }
                return node;
            default:
                return node;
        }
    }

    Proposition::TreeNode *Proposition::_negation_normal_form_to_conjunctive_normal_form(TreeNode *node) {
        if (node == nullptr)
            return nullptr;

        if (node->left)
            node->left = _negation_normal_form_to_conjunctive_normal_form(node->left);
        if (node->right)
            node->right = _negation_normal_form_to_conjunctive_normal_form(node->right);

        TreeNode *new_node;
        switch (node->token) {
            case '|':
                if (node->left->token == '|' && (std::isalnum(node->right->token) || node->right->token == '!')) {
                    new_node = new TreeNode(
                        '|',
                        node->left->left,
                        new TreeNode('|', node->left->right, node->right)
                    );
                    delete node->left;
                    delete node;
                    return _negation_normal_form_to_conjunctive_normal_form(new_node);
                }
                if ((std::isalnum(node->left->token) || node->left->token == '!') && node->right->token == '&') {
                    new_node = new TreeNode(
                        '&',
                        new TreeNode('|', _copy_tree(node->left), node->right->left),
                        new TreeNode('|', _copy_tree(node->left), node->right->right)
                    );
                    delete node->right;
                    delete node->left;
                    delete node;
                    return _negation_normal_form_to_conjunctive_normal_form(new_node);
                }
                return node;
            case '&':
                if (node->left->token == '&' && (std::isalnum(node->right->token) || node->right->token == '!')) {
                    new_node = new TreeNode(
                        '&',
                        node->left->left,
                        new TreeNode('&', node->left->right, node->right)
                    );
                    delete node->left;
                    delete node;
                    return _negation_normal_form_to_conjunctive_normal_form(new_node);
                }
                return node;
            default:
                return node;
        }
    }

}
