#if defined(NDEBUG)
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <memory>

// Do not modify it! Just use it!
enum NodeType {
    UNKNOWN,
    CONSTANT,
    UNARY,
    BINARY,
    VARIABLE,
    ASSIGNMENT,
};

// WORK HERE!!!
using namespace std;

class Context {
public:
    map<string, float> pairs;

    void setVariable(const string& variable, float value) {
        //pairs.insert(make_pair(variable, value));
        pairs[variable] = value;
    }

    float getVariable(const string& variable) const {
        auto it = pairs.find(variable);
        if (it != pairs.end()) return it->second;
        throw exception();
    }
    void dump(ostream& os) const {
        for (auto & pair : pairs) {
            os << pair.first << ": " << std::to_string(pair.second) << "\n";
        }
    }
};

class Node {
public:
    NodeType node_type;

    Node(NodeType node) : node_type(node) {}

    NodeType type() const {
        return node_type;
    }
    virtual string toString() const = 0;
    virtual float eval(Context& cn) const = 0;
};

class ConstantNode : public Node {
public:
    const float value;

    ConstantNode(const float value) : Node(CONSTANT) , value(value){}

    string toString() const override {return std::to_string(value);}
    float eval(Context& cn) const override {return value;}
};

class VariableNode : public Node {
    public:
    string variable;

    VariableNode(const string& name) :
        Node(VARIABLE), variable(name){}

    string toString() const override {return variable;}
    float eval(Context& cn) const override {return cn.getVariable(variable);};
};

class UnaryNode : public Node {
public:
    const char operation;
    std::shared_ptr<Node> pnode;


    UnaryNode(const char operation, const std::shared_ptr<Node> &node) :
        Node(UNARY), operation(operation), pnode(node){ }

    std::string toString() const override {
        string result = std::string(1, operation) + pnode->toString();
        return result;
    }

    float eval( Context& cn) const override {
        float v = pnode->eval(cn);
        return (operation ==  '-') ? -v : v;
    }
};

class BinaryNode : public Node {
public:
    const char operation;
    std::shared_ptr<Node> pleft_node;
    std::shared_ptr<Node> pright_node;

    BinaryNode(const char operation, const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right) :
        Node(BINARY), operation(operation), pleft_node(left), pright_node(right){}

    string toString() const override {
        string result = "(" + pleft_node->toString() + ") " + operation + " (" + pright_node->toString() + ")";
        return result;
    }

    float eval( Context& cn) const override {
        float rhs = pright_node->eval(cn);
        float lhs = pleft_node->eval(cn);

        switch (operation) {
            case '+':
                return lhs + rhs;
            case '-':
                return lhs - rhs;
            case '*':
                return lhs * rhs;
            case '/':
                return lhs / rhs;
            default:
                throw exception();
        }
    }
};

class AssignmentNode : public Node {
    public:
    string name;
    std::shared_ptr<Node> pnode;

    AssignmentNode(const string& name, const std::shared_ptr<Node>& pnode) :
        Node(ASSIGNMENT), name(name), pnode(pnode){}

    string toString() const override {
        string result = "(" + name + " = (" + pnode->toString() + "))";
        return result;
    }
    float eval( Context& cn) const override {
        const float val = pnode->eval(cn);
        cn.setVariable(name, val);
        return val;

    }
};

// DO NOT WRITE ANY CODE BELOW THIS LINE!
#ifndef TEST_BIRO

int main() {
    {
        // Context set
        Context ctx;
        std::cout << "# Context setVariable" << std::endl;
        ctx.setVariable("varA", 32.0f);
        ctx.setVariable("varB", 64.5f);

        // Context get
        {
            std::cout << "# Context getVariable" << std::endl;
            const float result = ctx.getVariable("varA");
            std::cout << "Context.getVariable: " << std::to_string(result) << std::endl;
            assert(result == 32.0f);
        }
        {
            std::cout << "# Context getVariable" << std::endl;
            const float result = ctx.getVariable("varB");
            std::cout << "Context.getVariable: " << std::to_string(result) << std::endl;
            assert(result == 64.5f);
        }

        {
            std::cout << "# Context dump " << std::endl;
            std::stringstream out;
            ctx.dump(out);
            const std::string result = out.str();
            std::cout << "Context dump: " << std::endl << out.str();
            assert(result == "varA: 32.000000\nvarB: 64.500000\n");
        }
    }

    {
        // Constant Node
        std::cout << "# Constant Node" << std::endl;

        ConstantNode targetNode(1024.0f);

        const NodeType type = targetNode.type();
        std::cout << "ConstantNode.type(): " << type << std::endl;
        assert(type == CONSTANT);

        const std::string resultStr = targetNode.toString();
        std::cout << "ConstantNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "1024.000000");

        Context emptyCtx;
        const float result = targetNode.eval(emptyCtx);
        std::cout << "ConstantNode.eval(emptyCtx): " << result << std::endl;
        assert(result == 1024.0f);
    }

    {
        // Variable Node
        std::cout << "# Variable Node" << std::endl;

        VariableNode targetNode("varD");

        const NodeType type = targetNode.type();
        std::cout << "VariableNode.type(): " << type << std::endl;
        assert(type == VARIABLE);

        const std::string resultStr = targetNode.toString();
        std::cout << "VariableNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "varD");

        Context ctx;
        ctx.setVariable("varD", 2048.0f);

        const float result = targetNode.eval(ctx);
        std::cout << "VariableNode.eval(ctx): " << result << std::endl;
        assert(result == 2048.0f);
    }

    {
        // Unary Node
        std::cout << "# Unary Node (+) with ConstantNode" << std::endl;
        std::shared_ptr<ConstantNode> constantNode(new ConstantNode(16.0f));

        UnaryNode targetNode('+', constantNode);

        const NodeType type = targetNode.type();
        std::cout << "UnaryNode.type(): " << type << std::endl;
        assert(type == UNARY);

        const std::string resultStr = targetNode.toString();
        std::cout << "UnaryNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "+16.000000");

        Context ctx;
        const float result = targetNode.eval(ctx);
        std::cout << "UnaryNode.eval(ctx): " << result << std::endl;
        assert(result == +16.0f);
    }

    {
        // Unary Node
        std::cout << "# Unary Node (-) with ConstantNode" << std::endl;
        std::shared_ptr<ConstantNode> constantNode(new ConstantNode(16.0f));

        UnaryNode targetNode('-', constantNode);

        const NodeType type = targetNode.type();
        std::cout << "UnaryNode.type(): " << type << std::endl;
        assert(type == UNARY);

        const std::string resultStr = targetNode.toString();
        std::cout << "UnaryNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "-16.000000");

        Context ctx;
        const float result = targetNode.eval(ctx);
        std::cout << "UnaryNode.eval(ctx): " << result << std::endl;
        assert(result == -16.0f);

        const long sharedPtrCount = constantNode.use_count();
        std::cout << "UnaryNode's internal shared ptr count is: " << sharedPtrCount << std::endl;
        assert(sharedPtrCount == 2);
    }

    {
        // Unary Node
        std::cout << "# Binary Node (+) with ConstantNodes" << std::endl;
        std::shared_ptr<ConstantNode> constantNodeA(new ConstantNode(16.0f));
        std::shared_ptr<ConstantNode> constantNodeB(new ConstantNode(32.0f));

        BinaryNode targetNode('+', constantNodeA, constantNodeB);

        const NodeType type = targetNode.type();
        std::cout << "BinaryNode.type(): " << type << std::endl;
        assert(type == BINARY);

        const std::string resultStr = targetNode.toString();
        std::cout << "BinaryNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "(16.000000) + (32.000000)");

        Context ctx;
        const float result = targetNode.eval(ctx);
        std::cout << "BinaryNode.eval(ctx): " << result << std::endl;
        assert(result == (16.0f + 32.0f));

        {
            const long sharedPtrCount = constantNodeA.use_count();
            std::cout << "BinaryNodes's internal shared ptr count for 'left hand side' is: " << sharedPtrCount << std::endl;
            assert(sharedPtrCount == 2);
        }
        {
            const long sharedPtrCount = constantNodeB.use_count();
            std::cout << "BinaryNodes's internal shared ptr count for 'right hand side' is: " << sharedPtrCount << std::endl;
            assert(sharedPtrCount == 2);
        }
    }

    {
        // Unary Node
        std::cout << "# Binary Node (-) with ConstantNodes" << std::endl;
        std::shared_ptr<ConstantNode> constantNodeA(new ConstantNode(16.0f));
        std::shared_ptr<ConstantNode> constantNodeB(new ConstantNode(32.0f));

        BinaryNode targetNode('-', constantNodeA, constantNodeB);

        const NodeType type = targetNode.type();
        std::cout << "BinaryNode.type(): " << type << std::endl;
        assert(type == BINARY);

        const std::string resultStr = targetNode.toString();
        std::cout << "BinaryNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "(16.000000) - (32.000000)");

        Context ctx;
        const float result = targetNode.eval(ctx);
        std::cout << "BinaryNode.eval(ctx): " << result << std::endl;
        assert(result == (16.0f - 32.0f));
    }

    {
        // Unary Node
        std::cout << "# Binary Node (*) with ConstantNodes" << std::endl;
        std::shared_ptr<ConstantNode> constantNodeA(new ConstantNode(16.0f));
        std::shared_ptr<ConstantNode> constantNodeB(new ConstantNode(32.0f));

        BinaryNode targetNode('*', constantNodeA, constantNodeB);

        const NodeType type = targetNode.type();
        std::cout << "BinaryNode.type(): " << type << std::endl;
        assert(type == BINARY);

        const std::string resultStr = targetNode.toString();
        std::cout << "BinaryNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "(16.000000) * (32.000000)");

        Context ctx;
        const float result = targetNode.eval(ctx);
        std::cout << "BinaryNode.eval(ctx): " << result << std::endl;
        assert(result == (16.0f * 32.0f));
    }

    {
        // Unary Node
        std::cout << "# Binary Node (/) with ConstantNodes" << std::endl;
        std::shared_ptr<ConstantNode> constantNodeA(new ConstantNode(32.0f));
        std::shared_ptr<ConstantNode> constantNodeB(new ConstantNode(16.0f));

        BinaryNode targetNode('/', constantNodeA, constantNodeB);

        const NodeType type = targetNode.type();
        std::cout << "BinaryNode.type(): " << type << std::endl;
        assert(type == BINARY);

        const std::string resultStr = targetNode.toString();
        std::cout << "BinaryNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "(32.000000) / (16.000000)");

        Context ctx;
        const float result = targetNode.eval(ctx);
        std::cout << "BinaryNode.eval(ctx): " << result << std::endl;
        assert(result == (32.0f / 16.0f));
    }

    {
        // Assignment Node
        std::cout << "# Assignment Node with ConstantNode" << std::endl;
        std::shared_ptr<ConstantNode> constantNodeA(new ConstantNode(32.0f));

        AssignmentNode targetNode("varD", constantNodeA);

        const NodeType type = targetNode.type();
        std::cout << "AssignmentNode.type(): " << type << std::endl;
        assert(type == ASSIGNMENT);

        const std::string resultStr = targetNode.toString();
        std::cout << "AssignmentNode.toString(): " << resultStr << std::endl;
        assert(resultStr == "(varD = (32.000000))");

        Context ctx;
        const float result = targetNode.eval(ctx);
        std::cout << "AssignmentNode.eval(ctx): " << result << std::endl;
        assert(result == 32.0f);

        {
            const float ctxResult = ctx.getVariable("varD");
            std::cout << "Context.getVariable(\"varD\"): " << ctxResult << std::endl;
            assert(ctxResult == 32.0f);
        }

        {
            const long sharedPtrCount = constantNodeA.use_count();
            std::cout << "AssignmentNode's internal shared ptr count is: " << sharedPtrCount << std::endl;
            assert(sharedPtrCount == 2);
        }
    }

    {
        // Complex Node tests
        std::cout << "# Complex Node tests" << std::endl;
        std::shared_ptr<ConstantNode> constantNodeA(new ConstantNode(32.0f));

        AssignmentNode targetNode("varD",
            std::make_shared<BinaryNode>('+',
                std::make_shared<BinaryNode>('*',
                    std::make_shared<ConstantNode>(10.0f),
                    std::make_shared<VariableNode>("varE")
                ),
                std::make_shared<UnaryNode>('-', std::make_shared<ConstantNode>(1024.0f))
            )
        );

        const std::string resultStr = targetNode.toString();
        std::cout << "Complex nodes .toString(): " << resultStr << std::endl;
        assert(resultStr == "(varD = (((10.000000) * (varE)) + (-1024.000000)))");

        Context ctx;
        ctx.setVariable("varE", 32.0f);

        const float result = targetNode.eval(ctx);
        std::cout << "Complex nodes  .eval(ctx): " << result << std::endl;
        assert(result == ((10.0f * 32.0f) + (-1024.0f))); // -704.0

        {
            const float ctxResult = ctx.getVariable("varD");
            std::cout << "Context.getVariable(\"varD\"): " << ctxResult << std::endl;
            assert(ctxResult == ((10.0f * 32.0f) + (-1024.0f))); // -704.0
        }
    }

    return 0;
}
#endif
