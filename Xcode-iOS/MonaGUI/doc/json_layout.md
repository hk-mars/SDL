
# JSON Layout Design

## Basic Elements

- view
- widget

## View

- single view
- multi view


## Widget

- object widget
- image widget
- label widget
- list widget
- slide widget
- scroll widget
- rich text widget


## View Elements

- widget
- view-control
- view-model

## Widget Elements

### Elements of Object Widget

- x, int
- y, int
- align, string
- x align: string
- y algin: string
- width, int, string
- height, int, string
- content
- enable
- visible



## Demos

[Json Online](https://jsononline.net/json-checker)

### A Start Logo

```json
{
  "view": "page_logo",
  "type": "single",
  "layer": [
    {
      "widget": "img_logo",
      "type": "image",
      "x": 0,
      "y": 0,
      "algin": "center"
    }
  ]
}
```

















