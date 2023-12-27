#ifndef READY_SET_BOOL_PROPOSITION_HPP
#define READY_SET_BOOL_PROPOSITION_HPP

namespace m42 {

    class Proposition {
    private:
        struct TreeNode {
            static const std::string valid_tokens;

            char token;
            TreeNode *left;
            TreeNode *right;

            TreeNode(char token, TreeNode *left, TreeNode *right);
            TreeNode(char token, TreeNode *left);
            explicit TreeNode(char token);
        };

        TreeNode *_root;
        std::map<char, size_t> _vars;

        Proposition();

        void _parse_formula(const std::string &formula);
        static void _delete_tree(TreeNode *node);
        static void _delete_stack(std::stack<TreeNode *> &stack);
        static TreeNode *_copy_tree(TreeNode *node);
        static std::string _postfix_notation(TreeNode *node);
        static void _print_node(TreeNode *node, int space);
        static bool _evaluate_node(TreeNode *node);
        void _substitute_values(TreeNode *node, const std::map<char, bool> &values);
        static TreeNode *_to_negation_normal_form(TreeNode *node);

    public:
        explicit Proposition(const std::string &formula);
        Proposition(const Proposition &other);
        Proposition(Proposition &&other) noexcept;
        Proposition &operator=(Proposition other);
        ~Proposition();

        [[maybe_unused]] void print_tree() const;
        [[nodiscard]] const std::map<char, size_t> &vars() const;
        [[nodiscard]] std::string postfix_notation() const;
        [[nodiscard]] bool evaluate() const;

        void substitute_values(const std::map<char, bool> &values);
        void to_negation_normal_form();
    };

}

#endif //READY_SET_BOOL_PROPOSITION_HPP
