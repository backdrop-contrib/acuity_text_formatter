# Text Formatter (Acuity Utils)

**Text Formatter (Acuity Utils)** provides a configurable text normalisation system for Backdrop CMS. It formats text fields, node titles, and user account names automatically on save to ensure consistent, clean data entry across your site.

---

## Features

### Field-Level Formatting (Widget)
* Custom **Acuity Text Formatter** widget for text fields:
  * Text
  * Long Text
  * Text with Summary
* Automatically formats field values on save.

---

### Entity-Wide Support
* Works across:
  * **Nodes** (including title field)
  * **Users** (including username)
  * Any **fieldable entity**
* Uses `hook_entity_presave()` and `hook_user_presave()` for consistent behaviour.

---

### Text Normalisation Options

* **Trim**
  * Removes leading and trailing whitespace.

* **Collapse Spaces**
  * Converts multiple spaces into a single space
    ```php
	(`"John   Smith"` → `"John Smith"`)
	```

* **Case Transformations**
  * Lowercase
  * Uppercase
  * CamelCase (Title Case)
  * Intercapped (CamelCase + Mc/Mac name handling)

---

### Intelligent Formatting

* **Smart Punctuation**
  * Capitalises after:
    * Hyphens (`Jean-Luc`)
    * Apostrophes (`O'Connor`)
    * Brackets (`(Example)`)
    * Periods (`Sentence one. Sentence two.`)
    * New lines (addresses, paragraphs)

* **Mc/Mac Name Logic**
  * Optional intelligent handling for names like:
    * `mcdonald` → `McDonald`
    * `macarthur` → `MacArthur`

---

### Custom Replacements

Define whole-word replacements such as:
- uk → UK
- usa → USA
- iphone → iPhone


**Case-insensitive**

**Whole-word matching (prevents issues like `Luke → LUKe`)**

**Applied after casing rules**

---

### Title Formatting (New)

* Apply formatting rules to **node titles per content type**
* Configurable via admin UI:
  * Trim
  * Collapse spaces
  * Case transform

---

### User Account Formatting (New)

* Apply formatting to **usernames (`$account->name`)**
* Optional and configurable:
  * Trim
  * Collapse spaces
  * Case transform

* Uses `hook_user_presave()` to ensure:
  * Runs early enough for username generators
  * Avoids late-stage conflicts

---

### Safety Features

* **Plain Text Enforcement**
  * Disables WYSIWYG editors on formatted fields
  * Prevents corruption of HTML markup during case conversion

* **Scoped Processing**
  * Only applies to fields using the Acuity widget
  * Avoids unintended global data mutation

---

## Requirements

- Backdrop CMS 1.x
- PHP 8.0+

---

## Installation

Install this module using standard Backdrop CMS instructions:

https://docs.backdropcms.org/documentation/extend-with-modules

Enable the module.

---

## Configuration

### 1. Global Settings

Go to: Configuration > Acuity Utils > Text Formatter Settings (/admin/config/acuity-utils/acuity_text)


Configure:

* Smart punctuation rules
* Mc/Mac name handling
* Custom replacements

---

### 2. Field Configuration

To apply formatting to a field:

1. Go to **Manage Fields** for your content type
2. Select a text field
3. Set **Widget Type** to **Acuity Text Formatter**
4. Configure:
   * Trim
   * Collapse spaces
   * Case transformation

---

### 3. Title Formatting

Tab: **Titles**

* Assign formatting rules per content type
* Applies to node titles on save

---

### 4. User Formatting

Tab: **Users**

* Configure formatting for usernames
* Recommended:
  * Enable **Trim**
  * Enable **Collapse Spaces**
  * Avoid aggressive case transformations unless required

---

## Usage Notes

### Username Safety

This module **does not automatically generate usernames**.

It only formats usernames **if explicitly configured**, preventing:

* Unexpected username changes
* User lockouts
* Conflicts with external modules

---

### Choosing the Right Mode

| Mode | Best Use |
|------|--------|
| Lowercase | Emails, IDs |
| Uppercase | Postcodes, codes |
| CamelCase | Titles, general text |
| Intercapped | Names, addresses |

---

### Collapse Spaces Guidance

| Use Case | Recommended |
|----------|------------|
| Names | ✅ Yes |
| Titles | ✅ Yes |
| Addresses | ⚠ Depends |
| Free text | ❌ Usually No |

---

## Known Behaviour

* Formatting occurs on **save**, not display
* Existing content is not retroactively processed
* Custom replacements apply **after casing rules**

---

## Issues

Report bugs and feature requests:

https://github.com/backdrop-contrib/acuity_text_formatter/issues

---

## About the "Acuity" Name
"Acuity" is the name used to organise a collection of modules and utilities. These tools are grouped under a unified name to streamline installation and make it easier for site maintainers to identify these suite of solutions.

Technically, the namespaces `acuity_` and `abms_` were chosen to enhance code readability and keep function names simple and easy to type.

While part of this larger Acuity family, this module is a standalone utility.

---

## Maintainers

- Steve Moorhouse (albanycomputers)
  https://github.com/albanycomputers

Contributions welcome.

---

## Credits

- Steve Moorhouse (Zulip: DrAlbany)
- Assisted by AI

---

## Sponsorship

- Albany Computer Services
  https://www.albany-computers.co.uk

- Albany Web Design
  https://www.albanywebdesign.co.uk

- Albany Hosting
  https://www.albany-hosting.co.uk

---

## License

GPL v2
See LICENSE.txt
