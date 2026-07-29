# Changelog

All notable changes to Text Formatter (Acuity Utils).

## 1.x-1.3.1 (unreleased)

### Changed

- **Behaviour change:** "Capitalize start of new lines (Paragraphs)" now
  applies on sites that had never saved the global settings form. The
  `capitalize_after_newline` key was read by the casing engine and offered on
  the form, but was missing from the default config — so it evaluated as NULL
  and the feature never ran, while the checkbox rendered unticked from the same
  absent value and so looked deliberately off rather than broken. It is now
  shipped as `true` alongside its five siblings, and `hook_update_1301()` sets
  it only where no explicit choice exists. Untick it on the Global tab if you
  do not want it. Affects camelcase and intercapped modes only.

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

### Removed

- The orphaned top-level `collapse_spaces` key in
  `acuity_text_formatter.settings`. Nothing ever read it — space collapsing is
  configured per field instance, per content type, or on the user name — so it
  read as a global default that silently did nothing. `hook_update_1301()`
  clears it from existing sites. Per-target settings are unaffected.

## 1.x-1.3.0

- Entity, user and title formatting; space normalisation.

## 1.x-1.2.0

- Title field support.

## 1.x-1.1.0

- Initial tagged release.
