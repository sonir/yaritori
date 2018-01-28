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
		"rect" : [ 230.0, 389.0, 640.0, 718.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
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
					"id" : "obj-8",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 223.0, 617.0, 45.0, 45.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 497.0, 156.5, 116.0, 31.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 497.0, 209.0, 41.0, 22.0 ],
					"style" : "",
					"text" : "/ 127."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-109",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 4,
					"outlettype" : [ "signal", "signal", "list", "list" ],
					"patching_rect" : [ 225.0, 433.666626, 85.0, 22.0 ],
					"style" : "",
					"text" : "omx.peaklim~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-130",
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 324.0, 305.666626, 47.0, 87.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 393.666687, 47.0, 133.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "Strom_L",
							"parameter_shortname" : "Storm",
							"parameter_type" : 0,
							"parameter_mmin" : -70.0,
							"parameter_mmax" : 6.0,
							"parameter_initial" : [ 0.0 ],
							"parameter_unitstyle" : 4
						}

					}
,
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"varname" : "Strom_L"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-128",
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 275.0, 305.666626, 47.0, 87.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 71.0, 393.666687, 39.0, 131.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "Rhythm_L",
							"parameter_shortname" : "Rhythm",
							"parameter_type" : 0,
							"parameter_mmin" : -70.0,
							"parameter_mmax" : 6.0,
							"parameter_initial" : [ 0.0 ],
							"parameter_unitstyle" : 4
						}

					}
,
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"varname" : "Rhythm_L"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-126",
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 226.0, 305.666626, 47.0, 87.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 24.0, 393.666687, 35.0, 131.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "Drone_L",
							"parameter_shortname" : "Drone",
							"parameter_type" : 0,
							"parameter_mmin" : -70.0,
							"parameter_mmax" : 6.0,
							"parameter_initial" : [ 0.0 ],
							"parameter_unitstyle" : 4
						}

					}
,
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"varname" : "Drone_L"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-114",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 324.0, 265.0, 40.0, 22.0 ],
					"style" : "",
					"text" : "storm"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-120",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 275.0, 265.0, 47.0, 22.0 ],
					"style" : "",
					"text" : "rhythm"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-122",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 225.0, 265.0, 41.0, 22.0 ],
					"style" : "",
					"text" : "drone"
				}

			}
, 			{
				"box" : 				{
					"focusbordercolor" : [ 0.701961, 0.415686, 0.886275, 1.0 ],
					"id" : "obj-146",
					"inactivecoldcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 225.0, 467.666626, 41.0, 129.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 177.0, 393.666687, 41.0, 131.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_linknames" : 1,
							"parameter_longname" : "Master_L",
							"parameter_shortname" : "L",
							"parameter_type" : 0,
							"parameter_mmin" : -70.0,
							"parameter_mmax" : 6.0,
							"parameter_initial" : [ 0 ],
							"parameter_unitstyle" : 4
						}

					}
,
					"textcolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"tricolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"varname" : "Master_L"
				}

			}
, 			{
				"box" : 				{
					"data" : 					{
						"clips" : [ 							{
								"filename" : "Macintosh HD:/Users/hana/Development/openFrameworks/of_v0.9.8_osx_release/apps/1802_CCMA/yaritori/src/max/_sliceBuf_for_app_src/soundproto_origin.wav",
								"filekind" : "audiofile",
								"loop" : 1,
								"content_state" : 								{
									"play" : [ 0 ],
									"formant" : [ 1.0 ],
									"pitchcorrection" : [ 0 ],
									"originallength" : [ 0.0, "ticks" ],
									"originallengthms" : [ 0.0 ],
									"basictuning" : [ 440 ],
									"timestretch" : [ 0 ],
									"slurtime" : [ 0.0 ],
									"mode" : [ "basic" ],
									"formantcorrection" : [ 0 ],
									"pitchshift" : [ 1.0 ],
									"speed" : [ 1.0 ],
									"followglobaltempo" : [ 0 ],
									"originaltempo" : [ 120.0 ],
									"quality" : [ "basic" ]
								}

							}
 ]
					}
,
					"id" : "obj-5",
					"maxclass" : "playlist~",
					"numinlets" : 1,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "signal", "", "dictionary" ],
					"patching_rect" : [ 225.0, 78.0, 150.0, 30.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-3",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 287.0, 161.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 3,
					"outlettype" : [ "signal", "signal", "signal" ],
					"patching_rect" : [ 225.0, 198.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "effect_sweep"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-114", 1 ],
					"order" : 0,
					"source" : [ "obj-1", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-114", 0 ],
					"order" : 1,
					"source" : [ "obj-1", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-120", 1 ],
					"order" : 0,
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-120", 0 ],
					"order" : 1,
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-122", 1 ],
					"order" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-122", 0 ],
					"order" : 1,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-146", 1 ],
					"source" : [ "obj-109", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-146", 0 ],
					"source" : [ "obj-109", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-130", 1 ],
					"source" : [ "obj-114", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-130", 0 ],
					"source" : [ "obj-114", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-128", 1 ],
					"source" : [ "obj-120", 1 ]
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
					"destination" : [ "obj-126", 1 ],
					"source" : [ "obj-122", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-126", 0 ],
					"source" : [ "obj-122", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 1 ],
					"midpoints" : [ 242.5, 412.666626, 300.5, 412.666626 ],
					"source" : [ "obj-126", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 0 ],
					"midpoints" : [ 235.5, 412.666626, 234.5, 412.666626 ],
					"source" : [ "obj-126", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 1 ],
					"midpoints" : [ 291.5, 412.666626, 300.5, 412.666626 ],
					"source" : [ "obj-128", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 0 ],
					"midpoints" : [ 284.5, 412.666626, 234.5, 412.666626 ],
					"source" : [ "obj-128", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 1 ],
					"midpoints" : [ 340.5, 412.666626, 300.5, 412.666626 ],
					"source" : [ "obj-130", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-109", 0 ],
					"midpoints" : [ 333.5, 412.666626, 234.5, 412.666626 ],
					"source" : [ "obj-130", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 1 ],
					"source" : [ "obj-146", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"source" : [ "obj-146", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 1 ],
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-128" : [ "Rhythm_L", "Rhythm", 0 ],
			"obj-120::obj-8::obj-13" : [ "Attack", "Attack", 2 ],
			"obj-146" : [ "Master_L", "L", 0 ],
			"obj-120::obj-8::obj-15" : [ "Makeup", "Makeup", 4 ],
			"obj-120::obj-8::obj-30" : [ "Ratio", "Ratio", 1 ],
			"obj-130" : [ "Strom_L", "Storm", 0 ],
			"obj-120::obj-8::obj-7" : [ "Output Gain", "Output Gain", 5 ],
			"obj-120::obj-8::obj-55" : [ "Threshold", "Threshold", 0 ],
			"obj-126" : [ "Drone_L", "Drone", 0 ],
			"obj-120::obj-8::obj-14" : [ "Release", "Release", 3 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "effect_sweep.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "soundproto_origin.wav",
				"bootpath" : "~/Development/openFrameworks/of_v0.9.8_osx_release/apps/1802_CCMA/yaritori/src/max/_sliceBuf_for_app_src",
				"patcherrelativepath" : "../../Development/openFrameworks/of_v0.9.8_osx_release/apps/1802_CCMA/yaritori/src/max/_sliceBuf_for_app_src",
				"type" : "WAVE",
				"implicit" : 1
			}
, 			{
				"name" : "drone.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "resonator.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "redux.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "ccma_drone_eq.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "eq.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "highpass.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "ccma_reverb.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "DryWet.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "lowshelf.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "yafr3.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "yafr.maxpat",
				"bootpath" : "/Users/Shared/Max 7/Examples/legacy-examples/effects/reverb",
				"patcherrelativepath" : "../../../Shared/Max 7/Examples/legacy-examples/effects/reverb",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "width.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "rhythm.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "ccma_rhythm_eq_first.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "ccma_rhythm_eq_second.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "redux_rhy.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "compressor.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "storm.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "SimpleDelay_First.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "drywet.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "SimpleDelay_Second.maxpat",
				"bootpath" : "~/Desktop/src",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
 ],
		"autosave" : 0
	}

}
