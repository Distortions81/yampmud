
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

#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merc.h"
#include "magic.h"

/* used to get new skills */
CH_CMD(do_gain)
{
  char buf[MAX_STRING_LENGTH];
  CHAR_DATA *trainer;
  int gn = 0, sn = 0;
  char arg1[MAX_STRING_LENGTH];
  char arg2[MAX_STRING_LENGTH];

  argument = one_argument(argument, arg1);
  argument = one_argument(argument, arg2);

  if (IS_NPC(ch))
    return;

  /* find a trainer */
  for (trainer = ch->in_room->people; trainer != NULL;
       trainer = trainer->next_in_room)
    if (IS_NPC(trainer) && IS_SET(trainer->act, ACT_GAIN))
      break;

  if (trainer == NULL || !can_see(ch, trainer))
  {
    send_to_char("You can't do that here.\n\r", ch);
    return;
  }

  if (arg1[0] == '\0')
  {
    do_say(trainer, "{aPardon me?{x");
    do_sayooc(trainer, "Try help gain");
    return;
  }

  if (!str_prefix(arg1, "list"))
  {
    int col;

    col = 0;

    sprintf(buf, "{c%-18s {W%-5s {c%-18s {W%-5s {c%-18s {W%-5s\n\r",
            "group", "cost", "group", "cost", "group", "cost");
    send_to_char(buf, ch);

    for (gn = 0; gn < MAX_GROUP; gn++)
    {
      if (group_table[gn].name == NULL)
        break;

      if (!ch->pcdata->group_known[gn] &&
          group_table[gn].rating[ch->class] > 0)
      {
        sprintf(buf, "{c%-18s {W%-5d ", group_table[gn].name,
                group_table[gn].rating[ch->class]);
        send_to_char(buf, ch);
        if (++col % 3 == 0)
          send_to_char("{x\n\r", ch);
      }
    }
    if (col % 3 != 0)
      send_to_char("\n\r", ch);

    send_to_char("\n\r", ch);

    col = 0;

    sprintf(buf,
            "{D%-5s {c%-16s {W%-5s {D%-5s {c%-16s {W%-5s {D%-5s {c%-16s {W%-5s{x\n\r",
            "level", "skill", "cost", "level", "skill", "cost", "level",
            "skill", "cost");
    send_to_char(buf, ch);

    for (sn = 2; sn < MAX_SKILL; sn++)
    {
      if (skill_table[sn].name == NULL)
        break;

      if (!ch->pcdata->learned[sn] &&
          skill_table[sn].rating[ch->class] > 0 &&
          skill_table[sn].spell_fun == spell_null)
      {
        sprintf(buf, "{w[{D%3d{w] {c%-18s {W%-3d{x ",
                skill_table[sn].skill_level[ch->class],
                skill_table[sn].name, skill_table[sn].rating[ch->class]);
        send_to_char(buf, ch);
        if (++col % 3 == 0)
          send_to_char("\n\r", ch);
      }
    }
    if (col % 3 != 0)
      send_to_char("\n\r", ch);
    return;
  }

  if (!str_cmp(arg1, "convert"))
  {
    if (ch->practice < 6)
    {
      act("$N tells you '{aYou are not yet ready.{x'", ch, NULL,
          trainer, TO_CHAR);
      return;
    }

    if (!str_cmp(arg2, "all"))
    {
      while (ch->practice > 5)
      {
        ch->practice -= 6;
        ch->train += 1;
      }
      act("$N helps you apply ALL your practice to training", ch, NULL,
          trainer, TO_CHAR);
      return;
    }
    else
    {
      act("$N helps you apply your practice to training", ch, NULL,
          trainer, TO_CHAR);
      ch->practice -= 6;
      ch->train += 1;
      return;
    }
  }

  if (!str_prefix(arg1, "study"))
  {
    if (ch->train < 1)
    {
      act("$N tells you '{aYou are not yet ready.{x'", ch, NULL,
          trainer, TO_CHAR);
      return;
    }

    if (!str_cmp(arg2, "all"))
    {
      ch->practice += (ch->train * 6);
      ch->train = 0;
      act("$N helps you apply ALL your training to practice", ch, NULL,
          trainer, TO_CHAR);
      return;
    }
    act("$N helps you apply your training to practice", ch, NULL, trainer,
        TO_CHAR);
    ch->train -= 1;
    ch->practice += 6;
    return;
  }

  if (!str_prefix(arg1, "points"))
  {
    if (ch->train < 2)
    {
      act("$N tells you '{aYou are not yet ready.{x'", ch, NULL,
          trainer, TO_CHAR);
      return;
    }

    if (ch->pcdata->points <= 40)
    {
      act("$N tells you '{aThere would be no point in that.{x'", ch,
          NULL, trainer, TO_CHAR);
      return;
    }

    act("$N trains you, and you feel more at ease with your skills.", ch,
        NULL, trainer, TO_CHAR);

    ch->train -= 2;
    ch->pcdata->points -= 1;
    ch->exp = (long) exp_per_level(ch, ch->pcdata->points) * ch->level;
    return;
  }

  /* else add a group/skill */

  gn = group_lookup(arg1);
  if (gn > 0)
  {
    if (ch->pcdata->group_known[gn])
    {
      act("$N tells you '{aYou already know that group!{x'", ch, NULL,
          trainer, TO_CHAR);
      return;
    }

    if (group_table[gn].rating[ch->class] <= 0)
    {
      act("$N tells you '{aThat group is beyond your powers.{x'", ch,
          NULL, trainer, TO_CHAR);
      return;
    }

    if (ch->train < group_table[gn].rating[ch->class])
    {
      act("$N tells you '{aYou are not yet ready for that group.{x'",
          ch, NULL, trainer, TO_CHAR);
      return;
    }

    /* add the group */
    gn_add(ch, gn);
    act("$N trains you in the art of $t", ch, group_table[gn].name,
        trainer, TO_CHAR);
    ch->train -= group_table[gn].rating[ch->class];
    return;
  }

  sn = skill_lookup(arg1);
  if (sn > -1)
  {
    if (skill_table[sn].spell_fun != spell_null)
    {
      act("$N tells you '{aYou must learn the full group.{x'", ch, NULL,
          trainer, TO_CHAR);
      return;
    }

    if (ch->pcdata->learned[sn])
    {
      act("$N tells you '{aYou already know that skill!{x'", ch, NULL,
          trainer, TO_CHAR);
      return;
    }

    if (skill_table[sn].rating[ch->class] <= 0)
    {
      act("$N tells you '{aThat skill is beyond your powers.{x'", ch,
          NULL, trainer, TO_CHAR);
      return;
    }

    if (ch->train < skill_table[sn].rating[ch->class])
    {
      act("$N tells you '{aYou are not yet ready for that skill.{x'",
          ch, NULL, trainer, TO_CHAR);
      return;
    }

    /* add the skill */
    ch->pcdata->learned[sn] = 1;
    act("$N trains you in the art of $t", ch, skill_table[sn].name,
        trainer, TO_CHAR);
    ch->train -= skill_table[sn].rating[ch->class];
    return;
  }

  act("$N tells you '{aI do not understand...{x'", ch, NULL, trainer,
      TO_CHAR);
}

/* RT spells and skills show the players spells (or skills) */

CH_CMD(do_spells)
{
  char spell_list[MAX_LEVEL + 1][MAX_STRING_LENGTH];
  char spell_columns[MAX_LEVEL + 1];
  int sn, lev, mana;
  bool found = false, showAll = false;
  char arg1[MAX_INPUT_LENGTH];
  char buf[MAX_STRING_LENGTH];

  if (IS_NPC(ch))
    return;

  argument = one_argument(argument, arg1);

  if (!strcmp(arg1, "all"))
    showAll = true;

  /* initilize data */
  for (lev = 0; lev < MAX_LEVEL + 1; lev++)
  {
    spell_columns[lev] = 0;
    spell_list[lev][0] = '\0';
  }

  for (sn = 2; sn < MAX_SKILL; sn++)
  {
    if (skill_table[sn].name == NULL)
      break;

    if (skill_table[sn].skill_level[ch->class] <= MAX_LEVEL &&
        skill_table[sn].spell_fun != spell_null &&
        ch->pcdata->learned[sn] > 0)
    {
      if (!showAll && ch->level < skill_table[sn].skill_level[ch->class])
        continue;

      found = true;
      lev = skill_table[sn].skill_level[ch->class];
      if (ch->level < lev)
        sprintf(buf, "{W%-19s{g  n/a      ", skill_table[sn].name);
      else
      {
        mana = UMAX(skill_table[sn].min_mana, 100 / (2 + ch->level - lev));
        sprintf(buf, "{W%-18s {g %3d {xmana  ", skill_table[sn].name, mana);
      }

      if (spell_list[lev][0] == '\0')
        sprintf(spell_list[lev], "\n\r{WLevel %4d: {g%s", lev, buf);
      else                      /* append */
      {
        if (++spell_columns[lev] % 2 == 0)
          strcat(spell_list[lev], "\n\r          ");
        strcat(spell_list[lev], buf);
      }
    }
  }

  /* return results */

  if (!found)
  {
    send_to_char("You know no spells.\n\r", ch);
    return;
  }

  for (lev = 0; lev < MAX_LEVEL + 1; lev++)
    if (spell_list[lev][0] != '\0')
      send_to_char(spell_list[lev], ch);
  send_to_char("\n\r", ch);
}

CH_CMD(do_skills)
{
  int sn, lev, i, level, lastlevel, toggle, ctoggle;
  bool found = false;
  bool race_has = false, showAll = false;
  char arg1[MAX_INPUT_LENGTH];
  char buf[MAX_STRING_LENGTH];
  char learnbuf[MSL];

  if (IS_NPC(ch))
    return;

  lastlevel = 0;
  toggle = 0;
  ctoggle = 0;

  argument = one_argument(argument, arg1);
  if (!strcmp(arg1, "all"))
    showAll = true;

  for (lev = 0; lev < (showAll ? MAX_LEVEL : ch->level); lev++)
    for (sn = 0; sn < MAX_SKILL; sn++)
    {

      if (skill_table[sn].spell_fun != spell_null)
        continue;

      if (skill_table[sn].name == NULL)
        break;

      race_has = false;
      for (i = 0; i < 5; i++)
      {
        if (pc_race_table[ch->race].skills == NULL)
          continue;
        if (pc_race_table[ch->race].skills[i] == NULL)
          break;

        if (!str_cmp(pc_race_table[ch->race].skills[i], skill_table[sn].name))
          race_has = true;
      }

      if (race_has)
        level = 1;
      else
        level = skill_table[sn].skill_level[ch->class];

      if (ch->pcdata->learned[sn] > 0)
        sprintf(learnbuf, "{G%%{g%-3d", ch->pcdata->learned[sn]);
      else
        sprintf(learnbuf, "{RN{rone");


      if (skill_table[sn].skill_level[ch->class] <= MAX_LEVEL || race_has)
      {
        found = true;

        if (lev == level)
        {
          if (race_has)
          {
            sprintf(buf, "%-19s\n\r", skill_table[sn].name);
          }
          else
          {
            if (level > lastlevel)
            {
              if (ctoggle == 0)
                ctoggle = 1;
              else
                ctoggle = 0;

              if (toggle == 0)
                send_to_char("\n\r", ch);

              sprintf(buf, "{c%-3d{C: %s%-19s %s {w| ", level,
                      ctoggle ? "{W" : "{w", skill_table[sn].name, learnbuf);
              send_to_char(buf, ch);
              toggle = 0;
            }
            else
            {
              sprintf(buf, "     %s%-19s %s {w| ", ctoggle ? "{W" : "{w",
                      skill_table[sn].name, learnbuf);
              send_to_char(buf, ch);

              if (toggle == 1)
                toggle = 0;
              else if (toggle == 0)
              {
                toggle = 1;
                send_to_char("\n\r", ch);
              }
            }
          }

          found = true;
          lastlevel = level;
        }
      }
    }

  /* return results */
  send_to_char("\n\r", ch);

  if (!found)
  {
    send_to_char("You are skill-less.\n\r", ch);
    return;
  }


}

/* shows skills, groups and costs (only if not bought) */
void list_group_costs(CHAR_DATA * ch)
{
  char buf[100];
  int gn, sn, col;

  if (IS_NPC(ch))
    return;

  col = 0;

  sprintf(buf, "{c%-18s {W%-5s {c%-18s {W%-5s {c%-18s {W%-5s{x\n\r",
          "group", "cp", "group", "cp", "group", "cp");
  send_to_char(buf, ch);

  for (gn = 0; gn < MAX_GROUP; gn++)
  {
    if (group_table[gn].name == NULL)
      break;

    if (!ch->gen_data->group_chosen[gn] && !ch->pcdata->group_known[gn] &&
        group_table[gn].rating[ch->class] > 0)
    {
      sprintf(buf, "{c%-18s {W%-5d{x ", group_table[gn].name,
              group_table[gn].rating[ch->class]);
      send_to_char(buf, ch);
      if (++col % 3 == 0)
        send_to_char("\n\r", ch);
    }
  }
  if (col % 3 != 0)
    send_to_char("\n\r", ch);
  send_to_char("\n\r", ch);

  col = 0;

  sprintf(buf, "{c%-18s {W%-2s {c%-18s {W%-2s {c%-18s {W%-2s{x\n\r",
          "skill", "cp", "skill", "cp", "skill", "cp");
  send_to_char(buf, ch);

  for (sn = 2; sn < MAX_SKILL; sn++)
  {
    if (skill_table[sn].name == NULL)
      break;

    if (!ch->gen_data->skill_chosen[sn] && ch->pcdata->learned[sn] == 0 &&
        skill_table[sn].spell_fun == spell_null &&
        skill_table[sn].rating[ch->class] > 0)
    {
      sprintf(buf, "{c%-18s {W%-2d{x ", skill_table[sn].name,
              skill_table[sn].rating[ch->class]);
      send_to_char(buf, ch);
      if (++col % 3 == 0)
        send_to_char("\n\r", ch);
    }
  }
  if (col % 3 != 0)
    send_to_char("\n\r", ch);
  send_to_char("\n\r", ch);

  sprintf(buf, "{WCreation points: {R%d{x\n\r", ch->pcdata->points);
  send_to_char(buf, ch);
  sprintf(buf, "{WExperience per level: {B%ld{x\n\r",
          exp_per_level(ch, ch->gen_data->points_chosen));
  send_to_char(buf, ch);
  return;
}

void list_group_chosen(CHAR_DATA * ch)
{
  char buf[100];
  int gn, sn, col;

  if (IS_NPC(ch))
    return;

  col = 0;

  sprintf(buf, "%-18s %-5s %-18s %-5s %-18s %-5s{x", "group", "cp", "group",
          "cp", "group", "cp\n\r");
  send_to_char(buf, ch);

  for (gn = 0; gn < MAX_GROUP; gn++)
  {
    if (group_table[gn].name == NULL)
      break;

    if (ch->gen_data->group_chosen[gn] &&
        group_table[gn].rating[ch->class] > 0)
    {
      sprintf(buf, "%-18s %-5d{x ", group_table[gn].name,
              group_table[gn].rating[ch->class]);
      send_to_char(buf, ch);
      if (++col % 3 == 0)
        send_to_char("\n\r", ch);
    }
  }
  if (col % 3 != 0)
    send_to_char("\n\r", ch);
  send_to_char("\n\r", ch);

  col = 0;

  sprintf(buf, "{c%-18s {W%-2s {c%-18s {W%-2s {c%-18s {W%-2s", "skill",
          "cp", "skill", "cp", "skill", "cp\n\r");
  send_to_char(buf, ch);

  for (sn = 2; sn < MAX_SKILL; sn++)
  {
    if (skill_table[sn].name == NULL)
      break;

    if (ch->gen_data->skill_chosen[sn] &&
        skill_table[sn].rating[ch->class] > 0)
    {
      sprintf(buf, "{c%-18s {W%-2d ", skill_table[sn].name,
              skill_table[sn].rating[ch->class]);
      send_to_char(buf, ch);
      if (++col % 3 == 0)
        send_to_char("\n\r", ch);
    }
  }
  if (col % 3 != 0)
    send_to_char("\n\r", ch);
  send_to_char("\n\r", ch);

  sprintf(buf, "{WCreation points: {R%d{x\n\r", ch->gen_data->points_chosen);
  send_to_char(buf, ch);
  sprintf(buf, "{WExperience per level: {B%ld{x\n\r",
          exp_per_level(ch, ch->gen_data->points_chosen));
  send_to_char(buf, ch);
  return;
}

long exp_per_level(CHAR_DATA * ch, int points)
{
  long expl, inc;

  if (IS_NPC(ch))
    return 1000;

  expl = 1000;
  inc = 500;

  if (points < 40)
    return 1000 * pc_race_table[ch->race].class_mult[ch->class] / 100;

  /* processing */
  points -= 40;

  while (points > 9)
  {
    expl += (long) inc;
    points -= 10;
    if (points > 9)
    {
      expl += (long) inc;
      inc *= 2;
      points -= 10;
    }
  }

  expl += (long) points *(long) inc / 10;

  return (long) expl *(long) pc_race_table[ch->race].class_mult[ch->
                                                                class] / 100;
}

/* this procedure handles the input parsing for the skill generator */
bool parse_gen_groups(CHAR_DATA * ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];
  char buf[100];
  int gn, sn, i;

  if (argument[0] == '\0')
    return false;

  argument = one_argument(argument, arg);

  if (!str_prefix(arg, "help"))
  {
    if (argument[0] == '\0')
    {
      do_help(ch, "group help");
      return true;
    }

    do_help(ch, argument);
    return true;
  }

  if (!str_prefix(arg, "add"))
  {
    if (argument[0] == '\0')
    {
      send_to_char("You must provide a skill name.\n\r", ch);
      return true;
    }

    gn = group_lookup(argument);
    if (gn != -1)
    {
      if (ch->gen_data->group_chosen[gn] || ch->pcdata->group_known[gn])
      {
        send_to_char("You already know that group!\n\r", ch);
        return true;
      }

      if (group_table[gn].rating[ch->class] < 1)
      {
        send_to_char("That group is not available.\n\r", ch);
        return true;
      }
      if (exp_per_level
          (ch,
           ch->gen_data->points_chosen +
           group_table[gn].rating[ch->class]) > 500000)
      {
        send_to_char("That will take you over the Exp/Level limit.\n\r", ch);
        return true;
      }

      sprintf(buf, "%s group added\n\r", group_table[gn].name);
      send_to_char(buf, ch);
      ch->gen_data->group_chosen[gn] = true;
      ch->gen_data->points_chosen += group_table[gn].rating[ch->class];
      gn_add(ch, gn);
      ch->pcdata->points += group_table[gn].rating[ch->class];
      return true;
    }

    sn = skill_lookup(argument);
    if (sn != -1)
    {
      if (ch->gen_data->skill_chosen[sn] || ch->pcdata->learned[sn] > 0)
      {
        send_to_char("You already know that skill!\n\r", ch);
        return true;
      }

      if (skill_table[sn].rating[ch->class] < 1 ||
          skill_table[sn].spell_fun != spell_null)
      {
        send_to_char("That skill is not available.\n\r", ch);
        return true;
      }
      sprintf(buf, "%s skill added\n\r", skill_table[sn].name);
      send_to_char(buf, ch);
      ch->gen_data->skill_chosen[sn] = true;
      ch->gen_data->points_chosen += skill_table[sn].rating[ch->class];
      ch->pcdata->learned[sn] = 1;
      ch->pcdata->points += skill_table[sn].rating[ch->class];
      return true;
    }

    send_to_char("No skills or groups by that name...\n\r", ch);
    return true;
  }

  if (!str_cmp(arg, "drop"))
  {
    if (argument[0] == '\0')
    {
      send_to_char("You must provide a skill to drop.\n\r", ch);
      return true;
    }

    gn = group_lookup(argument);
    if (gn != -1 && ch->gen_data->group_chosen[gn])
    {
      send_to_char("Group dropped.\n\r", ch);
      ch->gen_data->group_chosen[gn] = false;
      ch->gen_data->points_chosen -= group_table[gn].rating[ch->class];
      gn_remove(ch, gn);
      for (i = 0; i < MAX_GROUP; i++)
      {
        if (ch->gen_data->group_chosen[gn])
          gn_add(ch, gn);
      }
      ch->pcdata->points -= group_table[gn].rating[ch->class];
      return true;
    }

    sn = skill_lookup(argument);
    if (sn != -1 && ch->gen_data->skill_chosen[sn])
    {
      send_to_char("Skill dropped.\n\r", ch);
      ch->gen_data->skill_chosen[sn] = false;
      ch->gen_data->points_chosen -= skill_table[sn].rating[ch->class];
      ch->pcdata->learned[sn] = 0;
      ch->pcdata->points -= skill_table[sn].rating[ch->class];
      return true;
    }

    send_to_char("You haven't bought any such skill or group.\n\r", ch);
    return true;
  }

  if (!str_prefix(arg, "premise"))
  {
    do_help(ch, "premise");
    return true;
  }

  if (!str_prefix(arg, "list"))
  {
    list_group_costs(ch);
    return true;
  }

  if (!str_prefix(arg, "learned"))
  {
    list_group_chosen(ch);
    //        send_to_char("Sorry that is currently a buggy choice, but will be fixed soon.\n\r",ch);
    return true;
  }

  if (!str_prefix(arg, "info"))
  {
    do_groups(ch, argument);
    return true;
  }

  return false;
}

/* shows all groups, or the sub-members of a group */
CH_CMD(do_groups)
{
  char buf[100];
  int gn, sn, col;

  if (IS_NPC(ch))
    return;

  col = 0;

  send_to_char("Use the class command (help class) for a listing\n\r", ch);
  send_to_char("more in tune with your current character.\n\r\n\r", ch);

  if (argument[0] == '\0')
  {                             /* show all groups */

    for (gn = 0; gn < MAX_GROUP; gn++)
    {
      if (group_table[gn].name == NULL)
        break;
      if (ch->pcdata->group_known[gn])
      {
        sprintf(buf, "%-20s ", group_table[gn].name);
        send_to_char(buf, ch);
        if (++col % 3 == 0)
          send_to_char("\n\r", ch);
      }
    }
    if (col % 3 != 0)
      send_to_char("\n\r", ch);
    sprintf(buf, "Creation points: %d\n\r", ch->pcdata->points);
    send_to_char(buf, ch);
    return;
  }

  if (!str_cmp(argument, "all"))  /* show all groups */
  {
    for (gn = 0; gn < MAX_GROUP; gn++)
    {
      if (group_table[gn].name == NULL)
        break;
      sprintf(buf, "%-20s ", group_table[gn].name);
      send_to_char(buf, ch);
      if (++col % 3 == 0)
        send_to_char("\n\r", ch);
    }
    if (col % 3 != 0)
      send_to_char("\n\r", ch);
    return;
  }

  /* show the sub-members of a group */
  gn = group_lookup(argument);
  if (gn == -1)
  {
    send_to_char("No group of that name exist.\n\r", ch);
    send_to_char
      ("Type 'groups all' or 'info all' for a full listing.\n\r", ch);
    return;
  }

  for (sn = 0; sn < MAX_IN_GROUP; sn++)
  {
    if (group_table[gn].spells[sn] == NULL)
      break;
    sprintf(buf, "%-20s ", group_table[gn].spells[sn]);
    send_to_char(buf, ch);
    if (++col % 3 == 0)
      send_to_char("\n\r", ch);
  }
  if (col % 3 != 0)
    send_to_char("\n\r", ch);
}

/* shows all groups, or the sub-members of a group available to your class */
CH_CMD(do_class)
{
  char buf[100];
  int gn, sn, tn, col;

  if (IS_NPC(ch))
    return;

  col = 0;

  if (argument[0] == '\0')
  {                             /* show all groups */

    send_to_char("Groups you currently have:\n\r", ch);
    send_to_char("--------------------------\n\r", ch);
    for (gn = 0; gn < MAX_GROUP; gn++)
    {
      if (group_table[gn].name == NULL)
        break;
      if (ch->pcdata->group_known[gn])
      {
        sprintf(buf, "%-20s ", group_table[gn].name);
        send_to_char(buf, ch);
        if (++col % 3 == 0)
          send_to_char("\n\r", ch);
      }
    }
    if (col % 3 != 0)
      send_to_char("\n\r", ch);
    sprintf(buf, "Creation points: %d\n\r", ch->pcdata->points);
    send_to_char(buf, ch);
    return;
  }

  if (!str_cmp(argument, "all"))  /* show all groups */
  {
    send_to_char("Groups available to your class:\n\r", ch);
    send_to_char("-------------------------------\n\r", ch);
    for (gn = 0; gn < MAX_GROUP; gn++)
    {
      if (group_table[gn].name == NULL)
        break;
      if (group_table[gn].rating[ch->class] > 0)
      {
        sprintf(buf, "%-20s ", group_table[gn].name);
        send_to_char(buf, ch);
        if (++col % 3 == 0)
          send_to_char("\n\r", ch);
      }
    }
    if (col % 3 != 0)
      send_to_char("\n\r", ch);
    return;
  }

  /* show the sub-members of a group */
  gn = group_lookup(argument);
  if (gn == -1)
  {
    send_to_char("No group of that name exist.\n\r", ch);
    send_to_char("Type 'class all' for a full listing.\n\r", ch);
    return;
  }

  send_to_char("Spells available in this group:\n\r", ch);
  send_to_char("-------------------------------\n\r", ch);
  send_to_char
    ("{BLevel{x-{GSpell{x--------------- {BLevel{x-{GSpell{x---------------\n\r",
     ch);
  for (sn = 0; sn < MAX_IN_GROUP; sn++)
  {
    if (group_table[gn].spells[sn] == NULL)
      break;
    if ((tn = spell_avail(ch, group_table[gn].spells[sn])) >= 0)
    {
      sprintf(buf, "{B%-5d {G%-20s ",
              skill_table[tn].skill_level[ch->class],
              group_table[gn].spells[sn]);
      send_to_char(buf, ch);
      if (++col % 2 == 0)
        send_to_char("{x\n\r", ch);
    }
  }
  if (col % 2 != 0)
    send_to_char("{x\n\r", ch);
}

int spell_avail(CHAR_DATA * ch, const char *name)
{
  /* checks to see if a spell is available to a class */
  int sn, found = -1;

  if (IS_NPC(ch))
    return skill_lookup(name);

  for (sn = 2; sn < MAX_SKILL; sn++)
  {
    if (skill_table[sn].name == NULL)
      break;
    if (LOWER(name[0]) == LOWER(skill_table[sn].name[0]) &&
        !str_prefix(name, skill_table[sn].name))
    {
      if (skill_table[sn].skill_level[ch->class] <= LEVEL_ANCIENT)
        return sn;
    }
  }
  return found;
}

/* checks for skill improvement */
void check_improve(CHAR_DATA * ch, int sn, bool success, int multiplier)
{
  int chance;
  char buf[100];

  if (IS_NPC(ch))
    return;

  if (ch->level < skill_table[sn].skill_level[ch->class] ||
      skill_table[sn].rating[ch->class] == 0 || ch->pcdata->learned[sn] == 0
      || ch->pcdata->learned[sn] == 100)
    return;                     /* skill is not known */

  /* check to see if the character has a chance to learn */
  chance = 10 * int_app[get_curr_stat(ch, STAT_INT)].learn;
  chance /= (multiplier * skill_table[sn].rating[ch->class] * 4);
  chance += ch->level;

  if (number_range(1, 1000) > chance)
    return;

  /* now that the character has a CHANCE to learn, see if they really have */

  if (success)
  {
    chance = URANGE(5, 100 - ch->pcdata->learned[sn], 95);
    if (number_percent() < chance)
    {
      sprintf(buf, "You have become better at %s!\n\r", skill_table[sn].name);
      send_to_char(buf, ch);
      ch->pcdata->learned[sn]++;
      gain_exp(ch, 2 * skill_table[sn].rating[ch->class]);
    }
  }

  else
  {
    chance = URANGE(5, ch->pcdata->learned[sn] / 2, 30);
    if (number_percent() < chance)
    {
      sprintf(buf,
              "You learn from your mistakes, and your %s skill improves.\n\r",
              skill_table[sn].name);
      send_to_char(buf, ch);
      ch->pcdata->learned[sn] += number_range(1, 3);
      ch->pcdata->learned[sn] = UMIN(ch->pcdata->learned[sn], 100);
      gain_exp(ch, 2 * skill_table[sn].rating[ch->class]);
    }
  }
}

/* returns a group index number given the name */
int group_lookup(const char *name)
{
  int gn;

  for (gn = 0; gn < MAX_GROUP; gn++)
  {
    if (group_table[gn].name == NULL)
      break;
    if (LOWER(name[0]) == LOWER(group_table[gn].name[0]) &&
        !str_prefix(name, group_table[gn].name))
      return gn;
  }

  return -1;
}

/* recursively adds a group given its number -- uses group_add */
void gn_add(CHAR_DATA * ch, int gn)
{
  int i;

  ch->pcdata->group_known[gn] = true;
  for (i = 0; i < MAX_IN_GROUP; i++)
  {
    if (group_table[gn].spells[i] == NULL)
      break;
    group_add(ch, group_table[gn].spells[i], false);
  }
}

/* recusively removes a group given its number -- uses group_remove */
void gn_remove(CHAR_DATA * ch, int gn)
{
  int i;

  ch->pcdata->group_known[gn] = false;

  for (i = 0; i < MAX_IN_GROUP; i++)
  {
    if (group_table[gn].spells[i] == NULL)
      break;
    group_remove(ch, group_table[gn].spells[i]);
  }
}

/* use for processing a skill or group for addition  */
void group_add(CHAR_DATA * ch, const char *name, bool deduct)
{
  int sn, gn;

  if (IS_NPC(ch))               /* NPCs do not have skills */
    return;

  sn = skill_lookup(name);

  if (sn != -1)
  {
    if (ch->pcdata->learned[sn] == 0) /* i.e. not known */
    {
      ch->pcdata->learned[sn] = 1;
      if (deduct)
        ch->pcdata->points += skill_table[sn].rating[ch->class];
    }
    return;
  }

  /* now check groups */

  gn = group_lookup(name);

  if (gn != -1)
  {
    if (ch->pcdata->group_known[gn] == false)
    {
      ch->pcdata->group_known[gn] = true;
      if (deduct)
        ch->pcdata->points += group_table[gn].rating[ch->class];
    }
    gn_add(ch, gn);             /* make sure all skills in the group are known */
  }
}

/* used for processing a skill or group for deletion -- no points back! */

void group_remove(CHAR_DATA * ch, const char *name)
{
  int sn, gn;

  sn = skill_lookup(name);

  if (sn != -1)
  {
    ch->pcdata->learned[sn] = 0;
    return;
  }

  /* now check groups */

  gn = group_lookup(name);

  if (gn != -1 && ch->pcdata->group_known[gn] == true)
  {
    ch->pcdata->group_known[gn] = false;
    gn_remove(ch, gn);          /* be sure to call gn_add on all remaining
                                   groups */
  }
}

CH_CMD(do_showskill)
{
  char buf[MAX_STRING_LENGTH];
  int skill, class = 0;
  int i;

  strcpy(buf, "");
  /* argument = one_argument(argument,arg1); */

  if (argument[0] == '\0')
  {
    send_to_char("Syntax: showskill [skill/spell]\n\r", ch);
    return;
  }

  if ((skill = skill_lookup(argument)) == -1)
  {
    send_to_char("Skill not found.\n\r", ch);
    return;
  }

  sprintf(buf, "{xClasses and levels for %s{x:\n\r", skill_table[skill].name);
  send_to_char(buf, ch);
  /* send_to_char("{CClass Level Gain{x\n\r",ch); */
  /* send_to_char("{C----------- ----- ----{x\n\r",ch); */
  i = 0;
  for (class = 0; class < MAX_CLASS; class++)
  {
    if (skill_table[skill].skill_level[class] > LEVEL_ANCIENT)
      continue;
    i++;
    /* sprintf(buf,"{m%-11s {c%5d {m%4d{x\n\r",class_table[class].name,
       skill_table[skill].skill_level[class],
       skill_table[skill].rating[class]); */
    sprintf(buf, "{C%-13s{x: {c%3d  {x", class_table[class].name,
            skill_table[skill].skill_level[class]);
    buf[2] = UPPER(buf[2]);
    send_to_char(buf, ch);
    if (i == 3)
    {
      send_to_char("\n\r", ch);
      i = 0;
    }
  }
  return;
}

CH_CMD(do_showclass)
{
  char arg1[MAX_INPUT_LENGTH];
  char buf[MAX_STRING_LENGTH];

  int class, level, skill;

  int i;

  strcpy(buf, "");
  argument = one_argument(argument, arg1);

  if (arg1[0] == '\0')
  {
    send_to_char("Syntax: showclass [class]\n\r", ch);
    return;
  }
  if ((class = class_lookup(arg1)) == -1)
  {
    send_to_char("Class not found.\n\r", ch);
    return;
  }

  sprintf(buf, "{xSpells/skills for %s:{x\n\r", class_table[class].name);
  send_to_char(buf, ch);
  i = 0;
  for (level = 1; level <= LEVEL_ANCIENT; level++)
  {
    for (skill = 0; skill < MAX_SKILL; skill++)
    {
      if (skill_table[skill].skill_level[class] != level)
        continue;
      i++;
      sprintf(buf, "{CLevel %3d: {x: {c%-20s{x  ", level,
              skill_table[skill].name);
      send_to_char(buf, ch);
      if (i == 2)
      {
        send_to_char("\n\r", ch);
        i = 0;
      }
    }
  }
}
