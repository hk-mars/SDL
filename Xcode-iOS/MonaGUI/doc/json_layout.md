
# JSON Layout Design

## Basic Elements

- page
- view
- widget

## Page

- width, int, string
- height, int, string
- bg, string
- view

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
- content, string, optional
- enable, bool
- visible, bool
- background, string, color or image or buffer
- foreground, string, color or image or buffer
- effect

### Elements of Image Widget

- fg_effect
- motion_effect


## layout object

A layout object includes some widgets.

## layout layer

This means layout objects can be positioned on different layer.

We can choose which layer to show or hide for better drawing performance and UX.


## Demos

[Json Online](https://jsononline.net/json-checker)

### A Start Logo

```json
{
	"page": "page_logo",
	"view": "view_logo",
	"layer": [
		{
      		"widget": "img_logo",
      		"type": "image",
      		"image": "logo",
      		"x": 2,
      		"y": 2,
      		"algin": "center",
      		"bg": "gray",
      		"fg_effect": "alpha_blur",
      		"motion_effect": "slide",
      		"enable": false,
      		"visible": false,
    	},
  	]
}
```

















