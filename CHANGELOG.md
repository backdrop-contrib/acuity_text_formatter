# Changelog

All notable changes to Text Formatter (Acuity Utils).

## 1.x-1.3.1 (unreleased)

### Fixed

- `hook_entity_presave()` and `hook_node_presave()` are no longer declared with
  a by-reference first argument. Backdrop invokes both through
  `module_invoke_all()`, which passes its arguments by value, so the previous
  signatures emitted a PHP 8 warning on **every entity and node save
  site-wide**:

  ```
  Warning: acuity_text_formatter_entity_presave(): Argument #1 ($entity)
  must be passed by reference, value given in module_invoke_all()
  ```

  Individually harmless, but it writes a watchdog row per save, so bulk
  operations (imports, migrations) produced thousands of log entries and ran
  measurably slower. No behaviour change: an object variable holds a handle, so
  alterations made inside the hooks are still seen by the caller — which is how
  the sibling `hook_user_presave()` implementation has always worked.

## 1.x-1.3.0

- Entity, user and title formatting; space normalisation.

## 1.x-1.2.0

- Title field support.

## 1.x-1.1.0

- Initial tagged release.
