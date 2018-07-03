let run = (update, render, subscriptions, initState) => {
  let currentSubscribedTo = ref([]);
  let (m, c) = initState;
  let currentModel = ref(m);

  let onEvent = (event, runEffect) => {
    let (nModel, effect) = update(event, currentModel^);
    runEffect(effect, subscriptions(currentModel^));
    render(nModel);
  };

  let rec runEffect = (cmd, subs) =>
    Dom.setTimeout(
      () => {
        Cmd.run(cmd, onEvent(_, runEffect));
        let incomingSub = {
          let rec loop = s =>
            switch (s) {
            | Subs.Empty => []
            | Subs.NonEmpty(id, _) as sn => [(id, sn)]
            | Subs.Combine(s1, s2) => loop(s1) @ loop(s2)
            };
          loop(subs);
        };

        let currIds =
          List.map(fst,
            currentSubscribedTo^,
          );

        let (currSubs, newSubs) =
          List.partition(
            el => {
              List.exists(cid => cid == fst(el), currIds);
            },
            incomingSub,
          );

        let (_, toRemove) =
          List.partition(
            id =>
              List.exists(
                el => {
                  fst(el) == id;
                },
                currSubs,
              ),
            currIds,
          );

        Js.log(toRemove);

        List.iter(
          s => {
            let (id, sub) = s;
            currentSubscribedTo :=
              [
                (id, Subs.run(sub, onEvent(_, runEffect))),
                ...currentSubscribedTo^,
              ];
          },
          newSubs,
        );

        List.iter(
          id => {
            let (_, cancel) =
              List.find(
                e => {
                  fst(e) == id;
                },
                currentSubscribedTo^,
              );
            cancel();
            currentSubscribedTo :=
              List.filter(
                o => {
                  fst(o) != id;
                },
                currentSubscribedTo^,
              );
          },
          toRemove,
        );
      },
      0,
    );

  runEffect(c, subscriptions(m));
};
