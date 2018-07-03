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
          List.map(
            el => {
              let (id, _) = el;
              id;
            },
            currentSubscribedTo^,
          );

        let (currSubs, newSubs) =
          List.partition(
            el => {
              let (id, _) = el;
              List.exists(cid => cid == id, currIds);
            },
            incomingSub,
          );

        let (_, toRemove) =
          List.partition(
            id =>
              List.exists(
                el => {
                  let (cid, _) = el;
                  cid == id;
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
                  let (i, _) = e;
                  i == id;
                },
                currentSubscribedTo^,
              );
            cancel();
            currentSubscribedTo :=
              List.filter(
                o => {
                  let (i, _) = o;
                  i != id;
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
