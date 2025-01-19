# Evaluator for expressions with versions

A simple evaluator that verifies if a given version satisfies some logical expression like:

`version:<=2.15.0 AND NOT version:=2.12.2 AND NOT version:=2.12.3`

Supported Boolean operators are `NOT`, `AND` and `OR`, listed by precedence, from highest to lowest. For version comparisons, operators `==`, `=` (both for equal to), `!=` (not equal to), `<`, `<=`, `>` and `>=` are supported.

Argument to `parse` function is a string with expression and it returns `std::unique_ptr<expression_t>`, a pointer to final expression object. Invoking `evaluate` method on this object, with version to test passed, checks if the version satisfies expression. For example:

```c++
auto expression = parse("version:<=2.15.0 AND NOT version:=2.12.2 AND NOT version:=2.12.3");
expression->evaluate(version_t{ "2.12.1" }); // returns true
expression->evaluate(version_t{ "2.15.0" }); // returns true
expression->evaluate(version_t{ "2.12.2" }); // returns false
expression->evaluate(version_t{ "2.12.3" }); // returns false
```

