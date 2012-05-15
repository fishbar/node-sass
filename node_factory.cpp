#include "node_factory.hpp"

namespace Sass {
  
  Node_Impl* Node_Factory::alloc_Node_Impl(Node::Type type, string* file, size_t line)
  {
    Node_Impl* ip = new Node_Impl();
    ip->type = type;
    ip->file_name = file;
    ip->line_number = line;
    pool_.push_back(ip);
    return ip;
  }

  Node Node_Factory::operator()(Node::Type type, string* file, size_t line, const Token& t)
  {
    Node_Impl* ip = alloc_Node_Impl(type, file, line);
    ip->value.token = t;
    return Node(ip);
  }

  Node Node_Factory::operator()(Node::Type type, string* file, size_t line, size_t size)
  {
    Node_Impl* ip = alloc_Node_Impl(type, file, line);
    ip->children.reserve(size);
    return Node(ip);
  }

  Node Node_Factory::operator()(string* file, size_t line, double v)
  {
    Node_Impl* ip = alloc_Node_Impl(Node::number, file, line);
    ip->value.numeric = v;
    return Node(ip);
  }

  Node Node_Factory::operator()(string* file, size_t line, double v, const Token& t)
  {
    Node_Impl* ip = alloc_Node_Impl(Node::numeric_dimension, file, line);
    ip->value.dimension.numeric = v;
    ip->value.dimension.unit = t;
    return Node(ip);
  }
    
  Node Node_Factory::operator()(string* file, size_t line, double r, double g, double b, double a)
  {
    Node color((*this)(Node::numeric_color, file, line, 4));
    color << (*this)(file, line, r)
          << (*this)(file, line, g)
          << (*this)(file, line, b)
          << (*this)(file, line, a);
    return color;
  }

}