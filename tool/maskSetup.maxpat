{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 4,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"rect" : [ 159.0, 79.0, 647.0, 224.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-93",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 209.5, 677.0, 24.0, 24.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-68",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 257.0, 715.0, 50.0, 22.0 ],
					"style" : "",
					"text" : "store 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-66",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 237.5, 612.0, 102.0, 22.0 ],
					"style" : "",
					"text" : "if $i1 > 0 then $i1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-65",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 237.5, 641.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-56",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 255.0, 679.0, 54.0, 22.0 ],
					"style" : "",
					"text" : "store $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-53",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 342.5, 496.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-48",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 237.5, 587.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "+ 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-47",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 292.0, 524.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-157",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 237.5, 554.0, 50.0, 22.0 ],
					"style" : "",
					"text" : "pak 0 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-152",
					"maxclass" : "preset",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "preset", "int", "preset", "int" ],
					"patching_rect" : [ 237.5, 825.0, 77.0, 29.0 ],
					"preset_data" : [ 						{
							"number" : 1,
							"data" : [ 5, "obj-44", "tab", "int", 0, 5, "obj-52", "tab", "int", 0, 5, "obj-79", "flonum", "float", 0.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 0.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 0, 5, "obj-136", "number", "int", 0, 5, "obj-139", "number", "int", 0, 5, "obj-47", "number", "int", 1, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 1 ]
						}
, 						{
							"number" : 2,
							"data" : [ 5, "obj-44", "tab", "int", 0, 5, "obj-52", "tab", "int", 1, 5, "obj-79", "flonum", "float", 1.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 0.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 0, 5, "obj-136", "number", "int", 1, 5, "obj-139", "number", "int", 0, 5, "obj-47", "number", "int", 2, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 2 ]
						}
, 						{
							"number" : 3,
							"data" : [ 5, "obj-44", "tab", "int", 0, 5, "obj-52", "tab", "int", 3, 5, "obj-79", "flonum", "float", 1.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 1.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 0, 5, "obj-136", "number", "int", 2, 5, "obj-139", "number", "int", 0, 5, "obj-47", "number", "int", 3, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 3 ]
						}
, 						{
							"number" : 4,
							"data" : [ 5, "obj-44", "tab", "int", 0, 5, "obj-52", "tab", "int", 3, 5, "obj-79", "flonum", "float", 1.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 0.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 0, 5, "obj-136", "number", "int", 2, 5, "<invalid>", "number", "int", 0, 5, "<invalid>", "number", "int", 2, 5, "<invalid>", "number", "int", 3, 5, "obj-53", "number", "int", 1 ]
						}
, 						{
							"number" : 5,
							"data" : [ 5, "obj-44", "tab", "int", 1, 5, "obj-52", "tab", "int", 0, 5, "obj-79", "flonum", "float", 0.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 0.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 1, 5, "obj-136", "number", "int", 0, 5, "obj-139", "number", "int", 4, 5, "obj-47", "number", "int", 1, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 5 ]
						}
, 						{
							"number" : 6,
							"data" : [ 5, "obj-44", "tab", "int", 1, 5, "obj-52", "tab", "int", 1, 5, "obj-79", "flonum", "float", 1.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 0.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 1, 5, "obj-136", "number", "int", 1, 5, "obj-139", "number", "int", 4, 5, "obj-47", "number", "int", 2, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 6 ]
						}
, 						{
							"number" : 7,
							"data" : [ 5, "obj-44", "tab", "int", 1, 5, "obj-52", "tab", "int", 3, 5, "obj-79", "flonum", "float", 1.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 1.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 1, 5, "obj-136", "number", "int", 2, 5, "obj-139", "number", "int", 4, 5, "obj-47", "number", "int", 3, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 7 ]
						}
, 						{
							"number" : 8,
							"data" : [ 5, "obj-44", "tab", "int", 1, 5, "obj-52", "tab", "int", 2, 5, "obj-79", "flonum", "float", 0.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 1.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 1, 5, "obj-136", "number", "int", 3, 5, "obj-139", "number", "int", 4, 5, "obj-47", "number", "int", 4, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 8 ]
						}
, 						{
							"number" : 9,
							"data" : [ 5, "obj-44", "tab", "int", 2, 5, "obj-52", "tab", "int", 0, 5, "obj-79", "flonum", "float", 0.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 0.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 2, 5, "obj-136", "number", "int", 0, 5, "obj-139", "number", "int", 8, 5, "obj-47", "number", "int", 1, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 9 ]
						}
, 						{
							"number" : 10,
							"data" : [ 5, "obj-44", "tab", "int", 2, 5, "obj-52", "tab", "int", 1, 5, "obj-79", "flonum", "float", 1.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 0.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 2, 5, "obj-136", "number", "int", 1, 5, "obj-139", "number", "int", 8, 5, "obj-47", "number", "int", 2, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 10 ]
						}
, 						{
							"number" : 11,
							"data" : [ 5, "obj-44", "tab", "int", 2, 5, "obj-52", "tab", "int", 3, 5, "obj-79", "flonum", "float", 1.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 1.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 2, 5, "obj-136", "number", "int", 2, 5, "obj-139", "number", "int", 8, 5, "obj-47", "number", "int", 3, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 11 ]
						}
, 						{
							"number" : 12,
							"data" : [ 5, "obj-44", "tab", "int", 2, 5, "obj-52", "tab", "int", 2, 5, "obj-79", "flonum", "float", 0.0, 5, "obj-90", "flonum", "float", 0.001, 5, "obj-126", "flonum", "float", 1.0, 5, "obj-123", "flonum", "float", 0.0, 5, "obj-134", "number", "int", 2, 5, "obj-136", "number", "int", 3, 5, "obj-139", "number", "int", 8, 5, "obj-47", "number", "int", 4, 5, "obj-53", "number", "int", 1, 5, "obj-65", "number", "int", 12 ]
						}
 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-143",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 292.0, 496.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "+ 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-139",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 237.5, 524.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-137",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 237.5, 496.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "* 4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-136",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 292.0, 470.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-134",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 237.5, 470.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-119",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 589.0, 186.5, 39.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 238.5, 120.0, 39.0, 22.0 ],
					"style" : "",
					"text" : "down"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-120",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 557.5, 186.5, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 207.0, 120.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "up"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-121",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 638.5, 230.5, 50.0, 22.0 ],
					"style" : "",
					"text" : "0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-122",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 643.5, 265.5, 31.0, 22.0 ],
					"style" : "",
					"text" : "!- 0."
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-123",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 630.0, 186.5, 50.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 279.5, 120.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-124",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 713.5, 186.5, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 238.5, 144.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-125",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 682.0, 186.5, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 207.0, 144.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-126",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 557.5, 313.5, 50.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 227.5, 96.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-127",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 557.5, 265.5, 31.0, 22.0 ],
					"style" : "",
					"text" : "+ 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-128",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 557.5, 230.5, 50.0, 22.0 ],
					"style" : "",
					"text" : "0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-118",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 386.0, 186.5, 39.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 238.75, 45.0, 39.0, 22.0 ],
					"style" : "",
					"text" : "down"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-116",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 354.5, 186.5, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 207.25, 45.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "up"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-109",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 435.5, 230.5, 50.0, 22.0 ],
					"style" : "",
					"text" : "0.001"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-107",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 440.5, 265.5, 31.0, 22.0 ],
					"style" : "",
					"text" : "!- 0."
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-90",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 427.0, 186.5, 50.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 279.5, 45.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-86",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 510.5, 186.5, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 238.75, 69.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-82",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 479.0, 186.5, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 207.25, 69.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-79",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 354.5, 313.5, 50.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 227.5, 21.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-76",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 354.5, 265.5, 31.0, 22.0 ],
					"style" : "",
					"text" : "+ 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-75",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 354.5, 230.5, 50.0, 22.0 ],
					"style" : "",
					"text" : "0.001"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 756.0, 224.5, 150.0, 33.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 338.0, 45.0, 168.0, 20.0 ],
					"style" : "",
					"text" : "push to plus or minous value"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 751.0, 187.5, 150.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 338.0, 69.0, 150.0, 20.0 ],
					"style" : "",
					"text" : "click to init 0. or 1."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-69",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 175.5, 274.0, 135.0, 22.0 ],
					"style" : "",
					"text" : "if $i1 == 2 then 3 else 2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-57",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 175.5, 246.0, 174.0, 22.0 ],
					"style" : "",
					"text" : "if $i1 < 2 then $i1 else out2 $i1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-52",
					"maxclass" : "tab",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 175.5, 179.0, 142.0, 51.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 16.5, 96.0, 142.0, 51.0 ],
					"style" : "",
					"tabs" : [ "0", "1", "3", "2" ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "tab",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 2.75, 179.0, 169.0, 25.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 16.5, 43.0, 169.0, 25.0 ],
					"style" : "",
					"tabs" : [ "0", "1", "2" ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 469.0, 496.0, 150.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 517.5, 38.0, 150.0, 20.0 ],
					"style" : "",
					"text" : "windowID"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-36",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 469.0, 474.0, 150.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 517.5, 21.0, 150.0, 20.0 ],
					"style" : "",
					"text" : "click to clear mask"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 557.5, 157.0, 20.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 207.25, 97.0, 18.0, 20.0 ],
					"style" : "",
					"text" : "y"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 354.5, 157.0, 20.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 207.25, 22.0, 21.0, 20.0 ],
					"style" : "",
					"text" : "x"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 205.5, 150.0, 61.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 16.5, 75.0, 55.0, 20.0 ],
					"style" : "",
					"text" : "vertexID"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 79.0, 150.0, 82.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 16.5, 21.0, 62.0, 20.0 ],
					"style" : "",
					"text" : "windowID"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 532.0, 518.0, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 582.75, 60.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-25",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 500.5, 518.0, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 550.0, 60.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-26",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 469.0, 518.0, 29.5, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 518.5, 60.0, 29.5, 22.0 ],
					"style" : "",
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-21",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 6.0, 511.0, 191.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 16.5, 175.0, 182.0, 22.0 ],
					"style" : "",
					"text" : "/mask 0 0 0. 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 386.0, 554.0, 102.0, 22.0 ],
					"style" : "",
					"text" : "pak /resetMask 0"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 6.0, 460.0, 112.0, 22.0 ],
					"style" : "",
					"text" : "pak /mask 0 0 0. 0."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 6.0, 677.0, 147.0, 22.0 ],
					"style" : "",
					"text" : "udpsend 127.0.0.1 57140"
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"grad1" : [ 0.086275, 0.309804, 0.52549, 0.35 ],
					"grad2" : [ 0.086275, 0.309804, 0.52549, 0.35 ],
					"id" : "obj-99",
					"maxclass" : "panel",
					"mode" : 1,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 602.0, 466.0, 128.0, 128.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 10.0, 14.0, 489.0, 193.0 ],
					"proportion" : 0.39,
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"angle" : 270.0,
					"grad1" : [ 0.764706, 0.592157, 0.101961, 0.35 ],
					"grad2" : [ 0.764706, 0.592157, 0.101961, 0.35 ],
					"id" : "obj-100",
					"maxclass" : "panel",
					"mode" : 1,
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 617.0, 481.0, 128.0, 128.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 509.0, 14.0, 126.0, 77.0 ],
					"proportion" : 0.39,
					"style" : ""
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"midpoints" : [ 450.0, 300.0, 364.0, 300.0 ],
					"source" : [ "obj-107", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-107", 0 ],
					"source" : [ "obj-109", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-75", 0 ],
					"source" : [ "obj-116", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 0 ],
					"midpoints" : [ 395.5, 219.0, 445.0, 219.0 ],
					"source" : [ "obj-118", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-121", 0 ],
					"midpoints" : [ 598.5, 219.0, 648.0, 219.0 ],
					"source" : [ "obj-119", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-128", 0 ],
					"source" : [ "obj-120", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-122", 0 ],
					"source" : [ "obj-121", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-126", 0 ],
					"midpoints" : [ 653.0, 300.0, 567.0, 300.0 ],
					"source" : [ "obj-122", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-121", 1 ],
					"midpoints" : [ 639.5, 219.0, 679.0, 219.0 ],
					"order" : 0,
					"source" : [ "obj-123", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-128", 1 ],
					"midpoints" : [ 639.5, 219.0, 598.0, 219.0 ],
					"order" : 1,
					"source" : [ "obj-123", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-126", 0 ],
					"midpoints" : [ 723.0, 298.5, 567.0, 298.5 ],
					"source" : [ "obj-124", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-126", 0 ],
					"midpoints" : [ 691.5, 298.5, 567.0, 298.5 ],
					"source" : [ "obj-125", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-122", 1 ],
					"midpoints" : [ 567.0, 345.5, 687.0, 345.5, 687.0, 254.5, 665.0, 254.5 ],
					"order" : 0,
					"source" : [ "obj-126", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-127", 1 ],
					"midpoints" : [ 567.0, 345.5, 615.0, 345.5, 615.0, 254.5, 579.0, 254.5 ],
					"order" : 1,
					"source" : [ "obj-126", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 4 ],
					"midpoints" : [ 567.0, 397.25, 108.5, 397.25 ],
					"order" : 2,
					"source" : [ "obj-126", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-126", 0 ],
					"source" : [ "obj-127", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-127", 0 ],
					"source" : [ "obj-128", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-137", 0 ],
					"midpoints" : [ 247.0, 494.0, 247.0, 494.0 ],
					"source" : [ "obj-134", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-143", 0 ],
					"source" : [ "obj-136", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-139", 0 ],
					"source" : [ "obj-137", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-157", 0 ],
					"source" : [ "obj-139", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"midpoints" : [ 395.5, 588.5, 15.5, 588.5 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-47", 0 ],
					"source" : [ "obj-143", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 0 ],
					"source" : [ "obj-157", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"midpoints" : [ 541.5, 551.5, 478.5, 551.5 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"midpoints" : [ 510.0, 547.5, 478.5, 547.5 ],
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"midpoints" : [ 478.5, 546.5, 478.5, 546.5 ],
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-134", 0 ],
					"midpoints" : [ 12.25, 397.5, 247.0, 397.5 ],
					"order" : 0,
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 1 ],
					"midpoints" : [ 12.25, 331.5, 38.75, 331.5 ],
					"order" : 1,
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-157", 1 ],
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-66", 0 ],
					"source" : [ "obj-48", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-57", 0 ],
					"midpoints" : [ 185.0, 237.5, 185.0, 237.5 ],
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-143", 1 ],
					"source" : [ "obj-53", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-68", 1 ],
					"midpoints" : [ 264.5, 707.5, 297.5, 707.5 ],
					"source" : [ "obj-56", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-136", 0 ],
					"midpoints" : [ 185.0, 398.5, 301.5, 398.5 ],
					"order" : 0,
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-69", 0 ],
					"midpoints" : [ 340.0, 271.0, 185.0, 271.0 ],
					"source" : [ "obj-57", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 2 ],
					"midpoints" : [ 185.0, 363.5, 62.0, 363.5 ],
					"order" : 1,
					"source" : [ "obj-57", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-152", 0 ],
					"order" : 1,
					"source" : [ "obj-65", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-56", 0 ],
					"midpoints" : [ 247.0, 670.5, 264.5, 670.5 ],
					"order" : 0,
					"source" : [ "obj-65", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"source" : [ "obj-66", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-152", 0 ],
					"midpoints" : [ 266.5, 759.5, 247.0, 759.5 ],
					"source" : [ "obj-68", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-136", 0 ],
					"midpoints" : [ 185.0, 399.5, 301.5, 399.5 ],
					"order" : 0,
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 2 ],
					"midpoints" : [ 185.0, 383.0, 62.0, 383.0 ],
					"order" : 1,
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-76", 0 ],
					"source" : [ "obj-75", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"source" : [ "obj-76", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-107", 1 ],
					"midpoints" : [ 364.0, 345.5, 484.0, 345.5, 484.0, 254.5, 462.0, 254.5 ],
					"order" : 0,
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-76", 1 ],
					"midpoints" : [ 364.0, 345.5, 412.0, 345.5, 412.0, 254.5, 376.0, 254.5 ],
					"order" : 1,
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 3 ],
					"midpoints" : [ 364.0, 397.25, 85.25, 397.25 ],
					"order" : 2,
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 1 ],
					"midpoints" : [ 15.5, 496.0, 187.5, 496.0 ],
					"order" : 1,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"order" : 2,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-93", 0 ],
					"midpoints" : [ 15.5, 495.0, 219.0, 495.0 ],
					"order" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"midpoints" : [ 488.5, 298.5, 364.0, 298.5 ],
					"source" : [ "obj-82", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"midpoints" : [ 520.0, 298.5, 364.0, 298.5 ],
					"source" : [ "obj-86", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 1 ],
					"midpoints" : [ 436.5, 219.0, 476.0, 219.0 ],
					"order" : 0,
					"source" : [ "obj-90", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-75", 1 ],
					"midpoints" : [ 436.5, 219.0, 395.0, 219.0 ],
					"order" : 1,
					"source" : [ "obj-90", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-68", 0 ],
					"midpoints" : [ 219.0, 708.5, 266.5, 708.5 ],
					"source" : [ "obj-93", 0 ]
				}

			}
 ],
		"parameters" : 		{

		}
,
		"dependency_cache" : [  ],
		"autosave" : 0
	}

}
