
/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,	   *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *									   *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael	   *
 *  Chastain, Michael Quan, and Mitchell Tse.				   *
 *									   *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc	   *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.						   *
 *									   *
 *  Much time and thought has gone into this software and you are	   *
 *  benefitting.  We hope that you share your changes too.  What goes	   *
 *  around, comes around.						   *
 ***************************************************************************/

/***************************************************************************
*	ROM 2.4 is copyright 1993-1995 Russ Taylor			   *
*	ROM has been brought to you by the ROM consortium		   *
*	    Russ Taylor (rtaylor@pacinfo.com)				   *
*	    Gabrielle Taylor (gtaylor@pacinfo.com)			   *
*	    Brian Moore (rom@rom.efn.org)				   *
*	By using this code, you have agreed to follow the terms of the	   *
*	ROM license, in the file Rom24/doc/rom.license			   *
***************************************************************************/

/*************************************************************************** 
*       ROT 1.4 is copyright 1996-1997 by Russ Walsh                       * 
*       By using this code, you have agreed to follow the terms of the     * 
*       ROT license, in the file doc/rot.license                           * 
***************************************************************************/

/* this is a listing of all the commands and command related data */

/* for command types */
#define ML 	MAX_LEVEL           /* implementor */
#define L1	MAX_LEVEL - 1       /* creator */
#define L2	MAX_LEVEL - 2       /* supreme being */
#define L3	MAX_LEVEL - 3       /* deity */
#define L4 	MAX_LEVEL - 4       /* god */
#define L5	MAX_LEVEL - 5       /* immortal */
#define L6	MAX_LEVEL - 6       /* demigod */
#define L7	MAX_LEVEL - 7       /* angel */
#define L8	MAX_LEVEL - 8       /* avatar */
#define IM	LEVEL_IMMORTAL      /* angel */
#define AN  LEVEL_ANCIENT       /* Ancient */
#define HE	LEVEL_HERO          /* hero */

#define COM_INGORE	1

/*
 * Structure for a command in the command lookup table.
 */
struct cmd_type
{
  char *const name;
  DO_FUN *do_fun;
  sh_int position;
  sh_int level;
  sh_int tier;
  sh_int log;
  sh_int show;
};

/* the command table itself */
extern const struct cmd_type cmd_table[];

/*
 * Command functions.
 * Defined in act_*.c (mostly).
 */
DECLARE_DO_FUN(do_abort);
DECLARE_DO_FUN(do_abusy);
DECLARE_DO_FUN(do_aclear);
DECLARE_DO_FUN(do_addapply);
DECLARE_DO_FUN(do_addlag);
DECLARE_DO_FUN(do_advance);
DECLARE_DO_FUN(do_aedit);
DECLARE_DO_FUN(do_affects);
DECLARE_DO_FUN(do_afk);
DECLARE_DO_FUN(do_agree);
DECLARE_DO_FUN(do_alia);
DECLARE_DO_FUN(do_alias);
DECLARE_DO_FUN(do_alist);
DECLARE_DO_FUN(do_allow);
DECLARE_DO_FUN(do_allpeace);
DECLARE_DO_FUN(do_alock);
DECLARE_DO_FUN(do_ambush);
DECLARE_DO_FUN(do_ancient);
DECLARE_DO_FUN(do_anctalk);
DECLARE_DO_FUN(do_anew);
DECLARE_DO_FUN(do_announce);
DECLARE_DO_FUN(do_answer);
DECLARE_DO_FUN(do_areas);
DECLARE_DO_FUN(do_asave);
DECLARE_DO_FUN(do_ask);
DECLARE_DO_FUN(do_assassinate);
DECLARE_DO_FUN(do_astat);
DECLARE_DO_FUN(do_at);
DECLARE_DO_FUN(do_auction);
DECLARE_DO_FUN(do_autoall);
DECLARE_DO_FUN(do_autoassist);
DECLARE_DO_FUN(do_autocopy);
DECLARE_DO_FUN(do_autoexit);
DECLARE_DO_FUN(do_autogold);
DECLARE_DO_FUN(do_autolist);
DECLARE_DO_FUN(do_autoloot);
DECLARE_DO_FUN(do_autopeek);
DECLARE_DO_FUN(do_autosac);
DECLARE_DO_FUN(do_autosplit);
DECLARE_DO_FUN(do_autostore);
DECLARE_DO_FUN(do_award);
DECLARE_DO_FUN(do_backstab);
DECLARE_DO_FUN(do_backup);
DECLARE_DO_FUN(do_bamfin);
DECLARE_DO_FUN(do_bamfout);
DECLARE_DO_FUN(do_ban);
DECLARE_DO_FUN(do_bane);
DECLARE_DO_FUN(do_bank);
DECLARE_DO_FUN(do_bash);
DECLARE_DO_FUN(do_berserk);
DECLARE_DO_FUN(do_bet);
DECLARE_DO_FUN(do_blackjack);
DECLARE_DO_FUN(do_board);
DECLARE_DO_FUN(do_bonus);
DECLARE_DO_FUN(do_bprompt);
DECLARE_DO_FUN(do_brandish);
DECLARE_DO_FUN(do_brief);
DECLARE_DO_FUN(do_bug);
DECLARE_DO_FUN(do_busy);
DECLARE_DO_FUN(do_buy);
DECLARE_DO_FUN(do_call_wild);
DECLARE_DO_FUN(do_cast);
DECLARE_DO_FUN(do_cdonate);
DECLARE_DO_FUN(do_cgossip);
DECLARE_DO_FUN(do_challenge);
DECLARE_DO_FUN(do_channels);
DECLARE_DO_FUN(do_charinfo);
DECLARE_DO_FUN(do_circle);
DECLARE_DO_FUN(do_clan_donate);
DECLARE_DO_FUN(do_clans);
DECLARE_DO_FUN(do_clantalk);
DECLARE_DO_FUN(do_clanwho);
DECLARE_DO_FUN(do_class);
DECLARE_DO_FUN(do_clead);
DECLARE_DO_FUN(do_clone);
DECLARE_DO_FUN(do_close);
DECLARE_DO_FUN(do_colour);
DECLARE_DO_FUN(do_combine);
DECLARE_DO_FUN(do_commands);
DECLARE_DO_FUN(do_compact);
DECLARE_DO_FUN(do_compare);
DECLARE_DO_FUN(do_consent);
DECLARE_DO_FUN(do_consider);
DECLARE_DO_FUN(do_copyover);
DECLARE_DO_FUN(do_corner);
DECLARE_DO_FUN(do_count);
DECLARE_DO_FUN(do_credits);
DECLARE_DO_FUN(do_cscore);
DECLARE_DO_FUN(do_ctimer);
DECLARE_DO_FUN(do_deaf);
DECLARE_DO_FUN(do_decline);
DECLARE_DO_FUN(do_delet);
DECLARE_DO_FUN(do_delete);
DECLARE_DO_FUN(do_deny);
DECLARE_DO_FUN(do_description);
DECLARE_DO_FUN(do_dirt);
DECLARE_DO_FUN(do_disarm);
DECLARE_DO_FUN(do_disconnect);
DECLARE_DO_FUN(do_divorce);
DECLARE_DO_FUN(do_donate);
DECLARE_DO_FUN(do_doubleqp);
DECLARE_DO_FUN(do_doublexp);
DECLARE_DO_FUN(do_down);
DECLARE_DO_FUN(do_drag);
DECLARE_DO_FUN(do_drink);
DECLARE_DO_FUN(do_drop);
DECLARE_DO_FUN(do_drugs);
DECLARE_DO_FUN(do_dump);
DECLARE_DO_FUN(do_dupe);
DECLARE_DO_FUN(do_east);
DECLARE_DO_FUN(do_eat);
DECLARE_DO_FUN(do_echo);
DECLARE_DO_FUN(do_emote);
DECLARE_DO_FUN(do_enter);
DECLARE_DO_FUN(do_envenom);
DECLARE_DO_FUN(do_equipment);
DECLARE_DO_FUN(do_examine);
DECLARE_DO_FUN(do_exits);
DECLARE_DO_FUN(do_explored);
DECLARE_DO_FUN(do_feed);
DECLARE_DO_FUN(do_fill);
DECLARE_DO_FUN(do_finger);
DECLARE_DO_FUN(do_flag);
DECLARE_DO_FUN(do_flee);
DECLARE_DO_FUN(do_follow);
DECLARE_DO_FUN(do_force);
DECLARE_DO_FUN(do_forge);
DECLARE_DO_FUN(do_freeze);
DECLARE_DO_FUN(do_ftick);
DECLARE_DO_FUN(do_game);
DECLARE_DO_FUN(do_gain);
DECLARE_DO_FUN(do_get);
DECLARE_DO_FUN(do_ghost);
DECLARE_DO_FUN(do_give);
DECLARE_DO_FUN(do_gmote);
DECLARE_DO_FUN(do_gocial);
DECLARE_DO_FUN(do_gossip);
DECLARE_DO_FUN(do_goto);
DECLARE_DO_FUN(do_gouge);
DECLARE_DO_FUN(do_grats);
DECLARE_DO_FUN(do_group);
DECLARE_DO_FUN(do_groups);
DECLARE_DO_FUN(do_gset);
DECLARE_DO_FUN(do_gtc);
DECLARE_DO_FUN(do_gtell);
DECLARE_DO_FUN(do_guild);
DECLARE_DO_FUN(do_heal);
DECLARE_DO_FUN(do_hedit);
DECLARE_DO_FUN(do_help);
DECLARE_DO_FUN(do_hide);
DECLARE_DO_FUN(do_high_dice);
DECLARE_DO_FUN(do_holylight);
DECLARE_DO_FUN(do_home);
DECLARE_DO_FUN(do_howl);
DECLARE_DO_FUN(do_idea);
DECLARE_DO_FUN(do_ignor);
DECLARE_DO_FUN(do_ignore);
DECLARE_DO_FUN(do_immkiss);
DECLARE_DO_FUN(do_immtalk);
DECLARE_DO_FUN(do_imotd);
DECLARE_DO_FUN(do_incognito);
DECLARE_DO_FUN(do_inventory);
DECLARE_DO_FUN(do_invis);
DECLARE_DO_FUN(do_iquest);
DECLARE_DO_FUN(do_itake);
DECLARE_DO_FUN(do_kick);
DECLARE_DO_FUN(do_kill);
DECLARE_DO_FUN(do_knight);
DECLARE_DO_FUN(do_list);
DECLARE_DO_FUN(do_load);
DECLARE_DO_FUN(do_lock);
DECLARE_DO_FUN(do_log);
DECLARE_DO_FUN(do_long);
DECLARE_DO_FUN(do_look);
DECLARE_DO_FUN(do_lore);
DECLARE_DO_FUN(do_lscore);
DECLARE_DO_FUN(do_marry);
DECLARE_DO_FUN(do_madmin);
DECLARE_DO_FUN(do_massarena);
DECLARE_DO_FUN(do_medit);
DECLARE_DO_FUN(do_member);
DECLARE_DO_FUN(do_memory);
DECLARE_DO_FUN(do_mend);
DECLARE_DO_FUN(do_mfind);
DECLARE_DO_FUN(do_mlevel);
DECLARE_DO_FUN(do_mlist);
DECLARE_DO_FUN(do_mload);
DECLARE_DO_FUN(do_mob);
DECLARE_DO_FUN(do_mock);
DECLARE_DO_FUN(do_motd);
DECLARE_DO_FUN(do_mpedit);
DECLARE_DO_FUN(do_mpdump);
DECLARE_DO_FUN(do_mplist);
DECLARE_DO_FUN(do_mpoint);
DECLARE_DO_FUN(do_mpstat);
DECLARE_DO_FUN(do_mquest);
DECLARE_DO_FUN(do_msedit);
DECLARE_DO_FUN(do_mset);
DECLARE_DO_FUN(do_mstat);
DECLARE_DO_FUN(do_multioload);
DECLARE_DO_FUN(do_murde);
DECLARE_DO_FUN(do_murder);
DECLARE_DO_FUN(do_music);
DECLARE_DO_FUN(do_mwhere);
DECLARE_DO_FUN(do_newlock);
DECLARE_DO_FUN(do_nervestrike);
DECLARE_DO_FUN(do_newscore);
DECLARE_DO_FUN(do_nochannels);
DECLARE_DO_FUN(do_noclan);
DECLARE_DO_FUN(do_noemote);
DECLARE_DO_FUN(do_nofilter);
DECLARE_DO_FUN(do_nofollow);
DECLARE_DO_FUN(do_noloot);
DECLARE_DO_FUN(do_norestore);
DECLARE_DO_FUN(do_north);
DECLARE_DO_FUN(do_northeast);
DECLARE_DO_FUN(do_northwest);
DECLARE_DO_FUN(do_noshout);
DECLARE_DO_FUN(do_nosummon);
DECLARE_DO_FUN(do_note);
DECLARE_DO_FUN(do_notell);
DECLARE_DO_FUN(do_notitle);
DECLARE_DO_FUN(do_notran);
DECLARE_DO_FUN(do_oedit);
DECLARE_DO_FUN(do_ofind);
DECLARE_DO_FUN(do_olc);
DECLARE_DO_FUN(do_olist);
DECLARE_DO_FUN(do_oload);
DECLARE_DO_FUN(do_omni);
DECLARE_DO_FUN(do_ooc);
DECLARE_DO_FUN(do_open);
DECLARE_DO_FUN(do_order);
DECLARE_DO_FUN(do_oset);
DECLARE_DO_FUN(do_ostat);
DECLARE_DO_FUN(do_owhere);
DECLARE_DO_FUN(do_pack);
DECLARE_DO_FUN(do_pardon);
DECLARE_DO_FUN(do_password);
DECLARE_DO_FUN(do_peace);
DECLARE_DO_FUN(do_peek);
DECLARE_DO_FUN(do_pecho);
DECLARE_DO_FUN(do_perform);
DECLARE_DO_FUN(do_permban);
DECLARE_DO_FUN(do_pick);
DECLARE_DO_FUN(do_pkset);
DECLARE_DO_FUN(do_pktoggle);
DECLARE_DO_FUN(do_play);
DECLARE_DO_FUN(do_pload);
DECLARE_DO_FUN(do_pmote);
DECLARE_DO_FUN(do_pour);
DECLARE_DO_FUN(do_practice);
DECLARE_DO_FUN(do_pray);
DECLARE_DO_FUN(do_prefi);
DECLARE_DO_FUN(do_prefix);
DECLARE_DO_FUN(do_promote);
DECLARE_DO_FUN(do_prompt);
DECLARE_DO_FUN(do_propedit);
DECLARE_DO_FUN(do_propertylist);
DECLARE_DO_FUN(do_protect);
DECLARE_DO_FUN(do_psay);
DECLARE_DO_FUN(do_punload);
DECLARE_DO_FUN(do_purge);
DECLARE_DO_FUN(do_put);
DECLARE_DO_FUN(do_qgossip);
DECLARE_DO_FUN(do_qpgive);
DECLARE_DO_FUN(do_qspell);
DECLARE_DO_FUN(do_quaff);
DECLARE_DO_FUN(do_quest);
DECLARE_DO_FUN(do_questforge);
DECLARE_DO_FUN(do_questreset);
DECLARE_DO_FUN(do_qui);
DECLARE_DO_FUN(do_quiet);
DECLARE_DO_FUN(do_quit);
DECLARE_DO_FUN(do_quote);
DECLARE_DO_FUN(do_racetalk);
DECLARE_DO_FUN(do_randclan);
DECLARE_DO_FUN(do_rampage);
DECLARE_DO_FUN(do_read);
DECLARE_DO_FUN(do_reboo);
DECLARE_DO_FUN(do_reboot);
DECLARE_DO_FUN(do_recall);
DECLARE_DO_FUN(do_recho);
DECLARE_DO_FUN(do_recite);
DECLARE_DO_FUN(do_recover);
DECLARE_DO_FUN(do_redeem);
DECLARE_DO_FUN(do_redit);
DECLARE_DO_FUN(do_reform);
DECLARE_DO_FUN(do_reload);
DECLARE_DO_FUN(do_remove);
DECLARE_DO_FUN(do_rename);
DECLARE_DO_FUN(do_rent);
DECLARE_DO_FUN(do_repeat);
DECLARE_DO_FUN(do_repent);
DECLARE_DO_FUN(do_replay);
DECLARE_DO_FUN(do_reply);
DECLARE_DO_FUN(do_report);
DECLARE_DO_FUN(do_rerol);
DECLARE_DO_FUN(do_reroll);
DECLARE_DO_FUN(do_rescue);
DECLARE_DO_FUN(do_resets);
DECLARE_DO_FUN(do_resetxp);
DECLARE_DO_FUN(do_rest);
DECLARE_DO_FUN(do_restring);
DECLARE_DO_FUN(do_restore);
DECLARE_DO_FUN(do_return);
DECLARE_DO_FUN(do_rlist);
DECLARE_DO_FUN(do_rollback);
DECLARE_DO_FUN(do_rp);
DECLARE_DO_FUN(do_rset);
DECLARE_DO_FUN(do_rstat);
DECLARE_DO_FUN(do_rub);
DECLARE_DO_FUN(do_rules);
DECLARE_DO_FUN(do_sacrifice);
DECLARE_DO_FUN(do_say);
DECLARE_DO_FUN(do_sayic);
DECLARE_DO_FUN(do_sayooc);
DECLARE_DO_FUN(do_second);
DECLARE_DO_FUN(do_sedit);
DECLARE_DO_FUN(do_sell);
DECLARE_DO_FUN(do_set);
DECLARE_DO_FUN(do_scan);
DECLARE_DO_FUN(do_score);
DECLARE_DO_FUN(do_score_loki);
DECLARE_DO_FUN(do_score_new);
DECLARE_DO_FUN(do_scroll);
DECLARE_DO_FUN(do_sharpen);
DECLARE_DO_FUN(do_shout);
DECLARE_DO_FUN(do_show);
DECLARE_DO_FUN(do_showclass);
DECLARE_DO_FUN(do_showskill);
DECLARE_DO_FUN(do_shutdow);
DECLARE_DO_FUN(do_shutdown);
DECLARE_DO_FUN(do_shutup);
DECLARE_DO_FUN(do_sit);
DECLARE_DO_FUN(do_skills);
DECLARE_DO_FUN(do_sla);
DECLARE_DO_FUN(do_slay);
DECLARE_DO_FUN(do_sleep);
DECLARE_DO_FUN(do_slookup);
DECLARE_DO_FUN(do_slots);
DECLARE_DO_FUN(do_smote);
DECLARE_DO_FUN(do_sneak);
DECLARE_DO_FUN(do_snoop);
DECLARE_DO_FUN(do_socials);
DECLARE_DO_FUN(do_sockets);
DECLARE_DO_FUN(do_south);
DECLARE_DO_FUN(do_southeast);
DECLARE_DO_FUN(do_southwest);
DECLARE_DO_FUN(do_spells);
DECLARE_DO_FUN(do_split);
DECLARE_DO_FUN(do_spousetalk);
DECLARE_DO_FUN(do_squire);
DECLARE_DO_FUN(do_sset);
DECLARE_DO_FUN(do_stake);
DECLARE_DO_FUN(do_stand);
DECLARE_DO_FUN(do_stat);
DECLARE_DO_FUN(do_steal);
DECLARE_DO_FUN(do_strike);
DECLARE_DO_FUN(do_story);
DECLARE_DO_FUN(do_string);
DECLARE_DO_FUN(do_surrender);
DECLARE_DO_FUN(do_swalk);
DECLARE_DO_FUN(do_switch);
DECLARE_DO_FUN(do_tcolor);
DECLARE_DO_FUN(do_tell);
DECLARE_DO_FUN(do_thrust);
DECLARE_DO_FUN(do_tick);
DECLARE_DO_FUN(do_time);
DECLARE_DO_FUN(do_title);
DECLARE_DO_FUN(do_track);
DECLARE_DO_FUN(do_train);
DECLARE_DO_FUN(do_transfer);
DECLARE_DO_FUN(do_trip);
DECLARE_DO_FUN(do_trust);
DECLARE_DO_FUN(do_twit);
DECLARE_DO_FUN(do_typo);
DECLARE_DO_FUN(do_unalias);
DECLARE_DO_FUN(do_uncorner);
DECLARE_DO_FUN(do_unignor);
DECLARE_DO_FUN(do_unignore);
DECLARE_DO_FUN(do_unlock);
DECLARE_DO_FUN(do_unread);
DECLARE_DO_FUN(do_up);
DECLARE_DO_FUN(do_update);
DECLARE_DO_FUN(do_uptime);
DECLARE_DO_FUN(do_value);
DECLARE_DO_FUN(do_vape);
DECLARE_DO_FUN(do_vdpi);
DECLARE_DO_FUN(do_vdth);
DECLARE_DO_FUN(do_vdtr);
DECLARE_DO_FUN(do_verbose);
DECLARE_DO_FUN(do_vfree);
DECLARE_DO_FUN(do_visible);
DECLARE_DO_FUN(do_violate);
DECLARE_DO_FUN(do_vload);
DECLARE_DO_FUN(do_vnum);
DECLARE_DO_FUN(do_voodoo);
DECLARE_DO_FUN(do_vow);
DECLARE_DO_FUN(do_warn);
DECLARE_DO_FUN(do_wake);
DECLARE_DO_FUN(do_wear);
DECLARE_DO_FUN(do_weather);
DECLARE_DO_FUN(do_wecho);
DECLARE_DO_FUN(do_wedpost);
DECLARE_DO_FUN(do_west);
DECLARE_DO_FUN(do_where);
DECLARE_DO_FUN(do_whirlwind);
DECLARE_DO_FUN(do_who);
DECLARE_DO_FUN(do_whois);
DECLARE_DO_FUN(do_wimpy);
DECLARE_DO_FUN(do_wipe);
DECLARE_DO_FUN(do_wizhelp);
DECLARE_DO_FUN(do_wizlist);
DECLARE_DO_FUN(do_wizlock);
DECLARE_DO_FUN(do_wiznet);
DECLARE_DO_FUN(do_wizslap);
DECLARE_DO_FUN(do_worth);
DECLARE_DO_FUN(do_wspit);
DECLARE_DO_FUN(do_yell);
DECLARE_DO_FUN(do_zap);
DECLARE_DO_FUN(do_zecho);
DECLARE_DO_FUN(do_authname);
DECLARE_DO_FUN(do_badname);
DECLARE_DO_FUN(do_newname);
DECLARE_DO_FUN(do_olevel);
